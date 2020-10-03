#ifndef RANEBO
#define RANEBO


#include <string.h>

/* The version of Ranebo */
#define RANEBO_VERSION "0.2.1"

/* 3-bit color escapes (\e[{31-36}m) */
#define RANEBO_BASIC 1

/* 4-bit color escapes (\e[38;2;{0-255}m) */
#define RANEBO_EXTENDED 2

/* 21-bit RGB color escapes (\e[38;5;{0-255}m) */
#define RANEBO_TRUECOLOR 3


/* Returns the minimal buffer size needed to fit
 * the output of ranebo (with the null byte)
 * for a string of length strlen and the given colormode.
*/
int ranebosz(int strlen, int colormode);

/* Returns the minimal buffer size needed to fit
 * the output of ranebo_utf8 for the given string
 * and colormode. If the given string is not a
 * valid null-terminated UTF-8 string,
 * the behavior is undefined.
*/
int ranebosz_utf8(const char *string, int colormode);

/* Interpolates the given string with ANSI escape
 * sequences that color the string rainbow, and puts
 * the result into buf. The escapes used depend on the
 * colormode given - see RANEBO_* constants above.
 * If the given string does not end with a null byte
 * or the buf is not large enough to fit the output,
 * (see ranebosz above) the behavior is undefined.
*/
void ranebo(char *buf, const char *string, int colormode);

/* Interpolates the given UTF-8 string with ANSI escape
 * sequences that color the string rainbow, and puts
 * the result into buf. The escapes used depend on the
 * colormode given - see RANEBO_* constants above.
 * If the given string is not a valid null-terminated
 * UTF-8 string, or buf is not large enough to fit the output,
 * (see ranebosz_utf8 above) the behavior is undefined.
*/
void ranebo_utf8(char *buf, const char *string, int colormode);


#endif
