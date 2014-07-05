#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <stdarg.h>
#include "widget.h"
#include "config.h"
#include "structs.h"


/*******************
 * SIMPLE FUCTIONS *
 *******************/

/* CREATION */
widget * WCreate(){
    widget * new = (widget *)malloc(sizeof(widget));
    new->pict = NULL;
    new->first = NULL;
    new->pos.x = 0;
    new->pos.y = 0;
    new->container = NULL;
    new->content.n = 0;
    new->clickable = 1;
    new->timer.cnt = (int) SDL_GetTicks();
    new->timer.max = 0;
    new->type = FIXED;
}


/* DESTRUCTION */
void WFree(widget * w){
    int i;
    WLayer * cur, * tmp;

    // Free all the surfaces
    for (cur = w->pict->next; cur->next != w->pict; ){
	tmp = cur;
	cur = cur->next;
	SDL_FreeSurface(tmp->surf);
	free(tmp);
    }
    SDL_FreeSurface(w->pict->surf);
    free(w->pict);
	
    // Free all the inner widgets
    for (i=0; i<w->content.n; i++){
	WFree(w->content.tab[i]);
    }
    // And communicates to its container that it is free
    WRmContent(w->container, w);
    
    free(w);
}


/* CONTAINERS AND CONTENTS */
int WAddContent(widget * w_container, widget * w_content){
    if (w_container->content.n >= MAX_WIDGETS || w_container == NULL || w_container == NULL)
	return(0);

    w_container->content.tab[w_container->content.n] = w_content;
    w_container->content.n ++;
    w_content->container = w_container;

    return(1);
}


int WRmContent(widget * w_container, widget * w_content){
    int i = 0;
    char cont = 1;

    if (w_container == NULL || w_content == NULL){
	return(0);
    }

    for (i=0; i<w_container->content.n && cont; i++){
	if (w_container->content.tab[i] == w_content){
	    cont = 0;
	}
    }

    if (cont){
	return(0);
    }

    w_container->content.n --;
    w_container->content.tab[i] = w_container->content.tab[w_container->content.n];
    w_content->container = NULL;

    return(1);
}


/* INFOS */
int WGetHeight(widget * w){
    return((w->pict->surf)->h);
}


int WGetWidth(widget * w){
    return((w->pict->surf)->w);
}


widget * WArea(widget * w, int x, int y){
    /* Returns the widget in the ones contained by w which is under the position pos if there is one, or NULL */
    int i;

    for (i=0; i<w->content.n; i++){
	if (w->clickable && x >= w->content.tab[i]->pos.x && x < w->content.tab[i]->pos.x + WGetWidth(w->content.tab[i]) && y >= w->content.tab[i]->pos.y && y < w->content.tab[i]->pos.y + WGetHeight(w->content.tab[i]))
	    return(w->content.tab[i]);
    }

    return(NULL);
}


/* OTHERS */
int WBlit(widget * w){
    int i;

    SDL_BlitSurface(w->pict->surf, NULL, screen, &(w->pos));
    for (i=0; i<w->content.n; i++){
	SDL_BlitSurface(w->content.tab[i]->pict->surf, NULL, screen, &(w->content.tab[i]->pos));
    }

    return(1);
}


void WMove(widget * w, int x, int y){
    w->pos.x = x;
    w->pos.y = y;
}


/* Requires SDL_image */
widget * WLoadIMG(img_type type, int delay, int x, int y, char * url_base, ...){
    va_list ap;
    char * url;
    WLayer * lay, * last;
    
    widget * new = WCreate();
    new->timer.max = delay;
    new->pos.x = x;
    new->pos.y = y;
    new->type = type;
    // We load the first layer
    lay = (WLayer *) malloc(sizeof(WLayer));
    lay->surf = IMG_Load(url_base);
    lay->next = lay;
    new->pict = lay;
    new->first = lay->surf;
    last = lay;

    // We load every picture
    va_start(ap, url_base);
    while (url = va_arg(ap, char *)){	    // Stops at NULL
	lay = (WLayer *) malloc(sizeof(WLayer));
	lay->surf = IMG_Load(url);
	lay->next = new->pict;
	last->next = lay;
	last = lay;
    }
    va_end(ap);

    return(new);
}


void WFlip(widget * w){
    int i;
    widget * cur;
    int curtime = SDL_GetTicks();

    for (i=0; i<w->content.n; i++){
	cur = w->content.tab[i];
	if (cur->type != FIXED){
	    if (curtime - cur->timer.cnt >= cur->timer.max){
		cur->pict = cur->pict->next;
		cur->timer.cnt = curtime;
		if (cur->type == ANIM && cur->pict->surf == cur->first){
		    // If the image is only animated, we stop the animation after one loop
		    cur->type = FIXED;
		}
	    }
	}
    }
}



int WReloadAnim(widget * w){
    /* Reloads an animation */
    if (w->type != FIXED){
	return(0);
    }
    w->type = ANIM;
    
    return(1);
}
