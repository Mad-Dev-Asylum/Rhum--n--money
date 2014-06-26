#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include "widget.h"
#include "config.h"
#include "structs.h"


/* CREATION */
widget * WLoadBMP(char * url, int x, int y){
    widget * new = (widget *)malloc(sizeof(widget));

    new->surf = SDL_LoadBMP(url);
    new->pos.x = x;
    new->pos.y = y;

    return(new);
}


/* DESTRUCTION */
void WFree(widget * w){
    SDL_FreeSurface(w->surf);
    free(w);
}


/* INFOS */
int WGetHeight(widget * w){
    return((w->surf)->h);
}


int WGetWidth(widget * w){
    return((w->surf)->w);
}


/* OTHERS */
int WBlit(widget * w){
    return(SDL_BlitSurface(w->surf, NULL, screen, &(w->pos)));
}
