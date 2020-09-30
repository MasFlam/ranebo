#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "ranebo.h'

void printhelp(const char *execname)
{
	printf(
		"Ranebo v%s, the colorful shell util\n"
		"Usage: %s [option]... [--] [str]...\n"
		"\n"
		"Ranebo (rainbow) utilizes ANSI escapes to color its arguments rainbow.\n"
		"\n"
		"The available options are:\n"
		"  -h  --help       Show this help message\n"
		"  -v  --version    Show Ranebo version\n"
		"  -3  --basic      Use 3-bit color escapes\n"
		"  -8  --extended   Use 8-bit color escapes (default)\n"
		"  -t  --tc         Use 24-bit color (truecolor/RGB) escapes\n"
		"      --truecolor\n",
		RANEBO_VERSION,
		execname
	);
}

void printver()
{
	printf("Ranebo v%s\n", RANEBO_VERSION);
}

int main(int argc, const char **argv)
{
	if(argc == 0)
		return 0;
	else
	{
		int state = 1;
		int i;
		int colormode = 2;
		for(i = 1; i <= argc; ++i)
		{
			const char *arg = argv[i];
			switch(state)
			{
			case 1: // options
				if(strcmp("--help", arg) == 0)
				{
					printhelp(argv[0]);
					return 0;
				}
				else if(strcmp("--version", arg) == 0)
				{
					printver();
					return 0;
				}
				else if(strcmp("--basic", arg) == 0)
					colormode = RANEBO_BASIC;
				else if(strcmp("--extended", arg) == 0)
					colormode = RANEBO_EXTENDED;
				else if(strcmp("--truecolor", arg) == 0 || strcmp("--tc", arg) == 0)
					colormode = RANEBO_TRUECOLOR;
				else if(strcmp("--", arg) == 0)
					state = 2;
				else if(arg[0] == '-')
				{
					char c;
					++arg;
					while((c = *(arg++)) != '\0')
					{
						switch(c)
						{
							case 'h':
								printhelp();
								return 0;
							case 'v':
								printver();
								return 0;
							case '3':
								colormode = RANEBO_BASIC;
								break;
							case '8':
								colormode = RANEBO_EXTENDED;
								break;
							case 't':
								colormode = RANEBO_TRUECOLOR;
								break;
							default:
								fprintf(stderr, "Invalid flag option: %c\n", c);
								return 1;
						}
					}
				}
				else
				{
					state = 2;
					--i;
				}
				break;
			case 2: // strings
				int bufsz;
				char *buf = ranebo(arg, colormode, &bufsz);
				puts(buf);
				free(buf);
			}
		}
		return 0;
	}
}
