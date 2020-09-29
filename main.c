#include <stdio.h>
#include <string.h>

const char *RANEBO_VERSION = "0.1.0";

#include "args.c"

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
					printf(
						"Ranebo v%s, the colorful shell util\n"
						"Usage: %s [option]... [str]... [--] [str]...\n"
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
						argv[0]
					);
					return 0;
				}
				else if(strcmp("--version", arg) == 0)
				{
					printf("Ranebo v%s\n", RANEBO_VERSION);
					return 0;
				}
				else if(strcmp("--basic", arg) == 0)
					colormode = 1;
				else if(strcmp("--extended", arg) == 0)
					colormode = 2;
				else if(strcmp("--truecolor", arg) == 0 || strcmp("--tc", arg) == 0)
					colormode = 3;
				else if(arg[0] == '-')
				{
					char c;
					++arg;
					while((c = *(arg++)) != '\0')
					{
						switch(c)
						{
							case 'h':
							case 'v':
							case '3':
							case '8':
							case 't':
						}
					}
				}
			}
		}
	}
}
