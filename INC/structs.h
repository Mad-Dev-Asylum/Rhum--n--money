#ifndef DEF_STRUCTS
#define DEF_STRUCTS

#include <SDL/SDL.h>

/* STRUCTS */
typedef struct{
   SDL_Surface * surf;
   SDL_Rect pos;
}widget;

/* GLOBAL VARS */
SDL_Surface * screen;


#endif
