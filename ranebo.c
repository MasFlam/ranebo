#include "ranebo.h"

#include <stdlib.h>
#include "utf8utils.h"

const char *basic_colors[6] = {
	"\x1B[31m",
	"\x1B[33m",
	"\x1B[32m",
	"\x1B[36m",
	"\x1B[34m",
	"\x1B[35m"
};

const char *extended_colors[6] = {
	"\x1B[38;5;124m",
	"\x1B[38;5;130m",
	"\x1B[38;5;220m",
	"\x1B[38;5;028m",
	"\x1B[38;5;019m",
	"\x1B[38;5;055m"
};

const char *truecolors[6] = {
	"\x1B[38;2;255;000;000m",
	"\x1B[38;2;255;127;000m",
	"\x1B[38;2;255;255;000m",
	"\x1B[38;2;000;188;063m",
	"\x1B[38;2;000;104;255m",
	"\x1B[38;2;122;000;229m"
};

int ranebosz(int slen, int colormode)
{
	switch(colormode)
	{
	case RANEBO_BASIC:
		return slen * (5+1) + 4 + 1;
		break;
	default:
	case RANEBO_EXTENDED:
		return slen * (11+1) + 4 + 1;
		break;
	case RANEBO_TRUECOLOR:
		return slen * (19+1) + 4 + 1;
	}
}

int ranebosz_utf8(const char *str, int colormode)
{
	int utf8len = strlen_utf8(str);
	int len = strlen(str);
	return ranebosz(utf8len, colormode) + len - utf8len;
}

void ranebo(char *buf, const char *str, int colormode)
{
	char c;
	int i = 0, j = 0;
	while((c = str[i]) != '\0')
	{
		switch(colormode)
		{
		case RANEBO_BASIC:
			strcpy(buf + j, basic_colors[i % 6]);
			j += 5;
			break;
		default:
		case RANEBO_EXTENDED:
			strcpy(buf + j, extended_colors[i % 6]);
			j += 11;
			break;
		case RANEBO_TRUECOLOR:
			strcpy(buf + j, truecolors[i % 6]);
			j += 19;
		}
		buf[j++] = c;
		++i;
	}
	
	strcpy(buf + j, "\x1B[0m");
}

void ranebo_utf8(char *buf, const char *str, int colormode)
{
	const char *sptr = str;
	char *bufptr = buf;
	char c;
	int i = 0;
	while((c = *sptr) != '\0')
	{
		int cplen = codepoint_len(c);
		
		switch(colormode)
		{
		case RANEBO_BASIC:
			strcpy(bufptr, basic_colors[i % 6]);
			bufptr += 5;
			break;
		default:
		case RANEBO_EXTENDED:
			strcpy(bufptr, extended_colors[i % 6]);
			bufptr += 11;
			break;
		case RANEBO_TRUECOLOR:
			strcpy(bufptr, truecolors[i % 6]);
			bufptr += 19;
		}
		
		strncpy(bufptr, sptr, cplen);
		sptr += cplen;
		bufptr += cplen;
		++i;
	}
	
	strcpy(bufptr, "\x1B[0m");
}
