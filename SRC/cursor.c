#include "cursor.h"


cursor * WCreateCursor(widget * w, side s){
    cursor * new = (cursor *) malloc(sizeof(cursor));
    w->clickable = 0;
    new->w = w;

    switch (s){
	case TOP :
	    new->d_x = WGetWidth(w) / 2;
	    new->d_y = 0;
	    break;
	case TOP_RIGHT :
	    new->d_x = WGetWidth(w);
	    new->d_y = 0;
	    break;
	case RIGHT :
	    new->d_x = WGetWidth(w);
	    new->d_y = WGetHeight(w) / 2;
	    break;
	case BOTTOM_RIGHT :
	    new->d_x = WGetWidth(w);
	    new->d_y = WGetHeight(w);
	    break;
	case BOTTOM :
	    new->d_x = WGetWidth(w) / 2;
	    new->d_y = WGetHeight(w);
	    break;
	case BOTTOM_LEFT :
	    new->d_x = 0;
	    new->d_y = WGetHeight(w);
	    break;
	case LEFT :
	    new->d_x = 0;
	    new->d_y = WGetWidth(w) / 2;
	    break;
	case TOP_LEFT :
	    new->d_x = 0;
	    new->d_y = 0;
	    break;
    }

    return(new);
}


void WFreeCursor(cursor * c){
    WFree(c->w);
    free(c);
}


void WMoveCursor(cursor * c, int x, int y){
    WMove(c->w, x - c->d_x, y - c->d_y);
}
