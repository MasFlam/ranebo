#include "ranebo.h"

#include <stdlib.h>

const char *basic_colors[6] = {
	"31",
	"33",
	"32",
	"36",
	"34",
	"35"
}

char *ranebo(const char *str, int slen, int colormode, int *bufsz_out)
{
	int bufsz;
	
	switch(colormode)
	{
	case RANEBO_BASIC:
		bufsz = slen * 5 + 4 + 1;
		break;
	default:
	case RANEBO_EXTENDED:
		bufsz = slen * 11 + 4 + 1;
		break;
	case RANEBO_TRUECOLOR:
		bufsz = slen * 20 + 4 + 1;
	}
	
	*bufsz_out = bufsz;
	
	char *buf = calloc(bufsz, sizeof(char));
	
	char c;
	int i = 0, j = 0;
	while((c = str[i++]) != '\0')
	{
		switch(colormode)
		{
		case RANEBO_BASIC:
			
	}
	
	return buf;
}
