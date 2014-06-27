#ifndef DEF_WIDGET
#define DEF_WIDGET

#include <SDL/SDL.h>

/* DEFINE */
#define MAX_WIDGETS 64

/* STRUCTS */
typedef struct widget_struct widget;
typedef struct WList_struct WList;

typedef struct{
    int x;
    int y;
}position;

typedef struct WList_struct{
   widget * tab[MAX_WIDGETS];	    // What widget it contains
   int n;			    // How many widget it contains
}WList;

typedef struct widget_struct{
   SDL_Surface * surf;
   SDL_Rect pos;
   widget * container;		    // In which widget this one is contained
   WList content;		    // Its content
   char clickable;
}widget;

/* FUNCTIONS */
widget * WCreate();
void WFree(widget * w);
int WAddContent(widget * w_container, widget * w_content);
int WRmContent(widget * w_container, widget * w_content);
int WGetHeight(widget * w);
int WGetWidth(widget * w);
widget * WArea(widget * w, int x, int y);
widget * WLoadBMP(char * url, int x, int y);
int WBlit(widget * w);
void WMove(widget * w, int x, int y);
widget * WLoadIMG(char * url, int x, int y);


#endif
