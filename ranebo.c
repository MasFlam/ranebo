#include "ranebo.h"

#include <stdlib.h>

const char *basic_colors[6] = {
	"\e[31m",
	"\e[33m",
	"\e[32m",
	"\e[36m",
	"\e[34m",
	"\e[35m"
};

const char *extended_colors[6] = {
	"\e[38;5;124m",
	"\e[38;5;130m",
	"\e[38;5;220m",
	"\e[38;5;028m",
	"\e[38;5;019m",
	"\e[38;5;055m"
};

const char *truecolors[6] = {
	"\e[38;2;255;000;000m",
	"\e[38;2;255;127;000m",
	"\e[38;2;255;255;000m",
	"\e[38;2;000;188;063m",
	"\e[38;2;000;104;255m",
	"\e[38;2;122;000;229m"
};

int ranebosz(int slen, int colormode)
{
	switch(colormode)
	{
	case RANEBO_BASIC:
		return slen * 5 + 4 + 1;
		break;
	default:
	case RANEBO_EXTENDED:
		return slen * 11 + 4 + 1;
		break;
	case RANEBO_TRUECOLOR:
		return slen * 20 + 4 + 1;
	}
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
			j += 20;
		}
		buf[j++] = c;
		++i;
	}
	
	strcpy(buf + j, "\e[0m");
}
