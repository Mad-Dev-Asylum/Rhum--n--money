#ifndef DEF_CURSOR
#define DEF_CURSOR

#include "widget.h"

/* TYPEDEF */
typedef enum {TOP, TOP_RIGHT, RIGHT, BOTTOM_RIGHT, BOTTOM, BOTTOM_LEFT, LEFT, TOP_LEFT} side;

typedef struct{
    widget * w;
    int d_x;
    int d_y;
}cursor;

/* FUNCTIONS */
cursor * WCreateCursor(widget * w, side s);
void WFreeCursor(cursor * c);
void WMoveCursor(cursor * c, int x, int y);

#endif
