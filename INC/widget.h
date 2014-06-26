#ifndef DEF_WIDGET
#define DEF_WIDGET

#include <SDL/SDL.h>

/* STRUCTS */
typedef struct{
    int x;
    int y;
}position;

typedef struct{
   SDL_Surface * surf;
   position pos;
}widget;

/* FUNCTIONS */
widget * WLoadBMP(char * url, int x, int y);
void WFree(widget * w);
int WGetHeight(widget * w);
int WGetWidth(widget * w);
int WBlit(widget * w);


#endif
