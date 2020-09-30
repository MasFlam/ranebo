#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "ranebo.h"


void printhelp(const char *execname)
{
	int bufsz = ranebosz(strlen("Ranebo"), RANEBO_TRUECOLOR);
	char *titlebuf = calloc(bufsz, sizeof(char));
	ranebo(titlebuf, "Ranebo", RANEBO_TRUECOLOR);
	printf(
		"%s v%s, the colorful shell util\n"
		"Usage: %s [(option|string)...] [--] [str...]\n"
		"\n"
		"%s utilizes ANSI escapes to color its arguments rainbow.\n"
		"\n"
		"The available options are:\n"
		"  -h    --help       Show this help message\n"
		"  -v    --version    Show Ranebo version\n"
		"  -3    --basic      Use 3-bit color escapes\n"
		"  -8    --extended   Use 8-bit color escapes (default)\n"
		"  -t    --tc         Use 24-bit color (truecolor/RGB) escapes\n"
		"        --truecolor\n"
		"  -s S  --separator S\n"
		"        --sep S      Set the output separator to S (default is LF)\n",
		titlebuf,
		RANEBO_VERSION,
		execname,
		titlebuf
	);
	free(titlebuf);
}

void printver()
{
	int bufsz = ranebosz(strlen("Ranebo"), RANEBO_TRUECOLOR);
	char *titlebuf = calloc(bufsz, sizeof(char));
	ranebo(titlebuf, "Ranebo", RANEBO_TRUECOLOR);
	printf("%s v%s\n", titlebuf, RANEBO_VERSION);
	free(titlebuf);
}

void print_rainbo_arg(int i, int argc, const char *const *const argv, const char *separator, int colormode)
{
	const char *arg = argv[i];
	int bufsz = ranebosz(strlen(arg), colormode);
	char *buf = calloc(bufsz, sizeof(char));
	ranebo(buf, arg, colormode);
	if(i < argc - 1)
	{	printf("%s%s", buf, separator); }
	else
	{	puts(buf); }
	free(buf);
}


int main(int argc, const char *const *const argv)
{
	if(argc == 1)
	{	return 0; }
	else
	{
		int state = 1;
		int i;
		int colormode = 2;
		const char *separator = "\n";
		for(i = 1; i < argc; ++i)
		{
			const char *arg = argv[i];
			switch(state)
			{
			case 1:
			{	/* options */
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
				{	colormode = RANEBO_BASIC; }
				else if(strcmp("--extended", arg) == 0)
				{	colormode = RANEBO_EXTENDED; }
				else if(strcmp("--truecolor", arg) == 0 || strcmp("--tc", arg) == 0)
				{	colormode = RANEBO_TRUECOLOR; }
				else if(strcmp("--separator", arg) == 0 || strcmp("--sep", arg) == 0)
				{	state = 10; }
				else if(strcmp("--", arg) == 0)
				{	state = 2; }
				else if(strspn(arg, "-") == 2)
				{
					fprintf(stderr, "Invalid option: %s\n", arg);
					return 2;
				}
				else if(arg[0] == '-')
				{
					char c;
					++arg;
					while((c = *(arg++)) != '\0')
					{
						switch(c)
						{
							case 'h':
								printhelp(argv[0]);
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
							case 's':
								state = 10;
								goto skip_flags;
							default:
								fprintf(stderr, "Invalid flag option: -%c\n", c);
								return 2;
						}
					}
skip_flags:;
				}
				else
				{	/* string */
					print_rainbo_arg(i, argc, argv, separator, colormode);
				}
			} break;
			case 2:
			{	/* only strings */
				print_rainbo_arg(i, argc, argv, separator, colormode);
			} break;
			case 10:
			{	/* separator */
				separator = arg;
				state = 1;
			} break;
			}
		}
		return 0;
	}
}
