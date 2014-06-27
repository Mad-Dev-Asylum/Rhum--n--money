#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "widget.h"
#include "config.h"
#include "structs.h"


/*******************
 * SIMPLE FUCTIONS *
 *******************/

/* CREATION */
widget * WCreate(){
    widget * new = (widget *)malloc(sizeof(widget));
    new->surf = NULL;
    new->pos.x = 0;
    new->pos.y = 0;
    new->container = NULL;
    new->content.n = 0;
    new->clickable = 1;
}


/* DESTRUCTION */
void WFree(widget * w){
    int i;

    SDL_FreeSurface(w->surf);
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
    return((w->surf)->h);
}


int WGetWidth(widget * w){
    return((w->surf)->w);
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
widget * WLoadBMP(char * url, int x, int y){
    widget * new = WCreate();
    new->surf = SDL_LoadBMP(url);
    new->pos.x = x;
    new->pos.y = y;

    return(new);
}


int WBlit(widget * w){
    int i;

    SDL_BlitSurface(w->surf, NULL, screen, &(w->pos));
    for (i=0; i<w->content.n; i++){
	SDL_BlitSurface(w->content.tab[i]->surf, NULL, screen, &(w->content.tab[i]->pos));
    }

    return(1);
}


void WMove(widget * w, int x, int y){
    w->pos.x = x;
    w->pos.y = y;
}


/* Requires SDL_image */
widget * WLoadIMG(char * url, int x, int y){
    widget * new = WCreate();
    new->surf = IMG_Load(url);
    new->pos.x = x;
    new->pos.y = y;

    return(new);
}
