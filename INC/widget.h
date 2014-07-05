#ifndef DEF_WIDGET
#define DEF_WIDGET

#include <SDL/SDL.h>

/* DEFINE */
#define MAX_WIDGETS 64

/* STRUCTS */
typedef struct widget_struct widget;
typedef struct WList_struct WList;
typedef struct WLayer_struct WLayer;
typedef enum{
    FIXED,	// Fixed image, only the first layer is used
    ANIM,	// Animation looping only once
    LOOP	// Forever looping animation
}img_type;

typedef struct{
    int x;
    int y;
}position;

typedef struct{
    int cnt;
    int max;
}WCounter;

typedef struct WLayer_struct{
    SDL_Surface * surf;
    WLayer * next;
}WLayer;

typedef struct WList_struct{
   widget * tab[MAX_WIDGETS];	    // What widget it contains
   int n;			    // How many widget it contains
}WList;

typedef struct widget_struct{
    SDL_Surface * first;	    // The first image
    WLayer * pict;		    // The picture
    SDL_Rect pos;		    // Its position
    widget * container;		    // In which widget this one is contained
    WList content;		    // Its content
    char clickable;		    // If it's clickable or "transparent"
    WCounter timer;		    // For animated widget, useful to time the cycling of layers
    img_type type;
}widget;

/* FUNCTIONS */
widget * WCreate();
void WFree(widget * w);
int WAddContent(widget * w_container, widget * w_content);
int WRmContent(widget * w_container, widget * w_content);
int WGetHeight(widget * w);
int WGetWidth(widget * w);
widget * WArea(widget * w, int x, int y);
int WBlit(widget * w);
void WMove(widget * w, int x, int y);
widget * WLoadIMG(img_type type, int delay, int x, int y, char * url_base, ...);
void WFlip(widget * w);
int WReloadAnim(widget * w);

#endif
