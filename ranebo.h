#ifndef RANEBO
#define RANEBO


#include <string.h>


#define RANEBO_VERSION "0.1.0"

#define RANEBO_BASIC 1
#define RANEBO_EXTENDED 2
#define RANEBO_TRUECOLOR 3

char *ranebo(const char *str, int strlen, int colormode, int *bufsz);

char *ranebo(const char *str, int colormode, int *bufsz) {
	return ranebo(str, strlen(str), colormode, bufsz);
}

#endif
