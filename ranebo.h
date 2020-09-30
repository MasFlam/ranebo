#ifndef RANEBO
#define RANEBO


#include <string.h>


#define RANEBO_VERSION "0.1.0"

#define RANEBO_BASIC 1
#define RANEBO_EXTENDED 2
#define RANEBO_TRUECOLOR 3


int ranebosz(int strlen, int colormode);

void ranebo(char *buf, const char *str, int colormode);


#endif
