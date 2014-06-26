#ifndef DEF_WIDGET
#define DEF_WIDGET

#include "structs.h"

widget * WLoadBMP(char * url, int x, int y);
void WFree(widget * w);
int WGetHeight(widget * w);
int WGetWidth(widget * w);
int WBlit(widget * w);


#endif
