#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "ranebo.h"
#include "utf8utils.h"


void printhelp(const char *execname)
{
	int bufsz = ranebosz(strlen("Ranebo"), RANEBO_EXTENDED);
	char *titlebuf = calloc(bufsz, sizeof(char));
	ranebo(titlebuf, "Ranebo", RANEBO_EXTENDED);
	printf(
		"%s v%s, the colorful shell util\n"
		"Usage: %s [(option|string)...] [--] [string...]\n"
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
		"        --sep S      Set the output separator to S (default is LF)\n"
		"  -u    --utf8       Use UTF-8 as the input and output encoding\n"
		"  -a    --ascii      Use ASCII as the input and output encoding (default)\n"
		"  -S    --stdin      Read strings also from stdin\n"
		"\n"
		"All arguments after `--` will not be parsed as options.\n"
		"You can chain flags into one argument, like this:\n"
		"    ranebo -3s . www example com\n"
		"The above would result in `\e[31mw\e[33mw\e[32mw\e[0m.\e[31me\e[33mx\e[32ma\e[36mm\e[34mp\e[35ml\e[31me\e[0m.\e[31mc\e[33mo\e[32mm\e[0m.` being printed to stdout.\n"
		"The flag that takes an argument should come last in the chain.\n",
		titlebuf,
		RANEBO_VERSION,
		execname,
		titlebuf
	);
	free(titlebuf);
}

void printver()
{
	int bufsz = ranebosz(strlen("Ranebo"), RANEBO_EXTENDED);
	char *titlebuf = calloc(bufsz, sizeof(char));
	
	ranebo(titlebuf, "Ranebo", RANEBO_EXTENDED);
	printf("%s v%s\n", titlebuf, RANEBO_VERSION);
	
	free(titlebuf);
}

/* Return 0 if successful, 1 otherwise. */
int print_ranebo_arg(const char *arg, const char *separator, int colormode, int use_utf8)
{
	if(use_utf8)
		if(!is_valid_utf8(arg))
		{
			fputs("Invalid UTF-8\n", stderr);
			return 1;
		}
	
	int bufsz;
	if(use_utf8)
		bufsz = ranebosz_utf8(arg, colormode);
	else
		bufsz = ranebosz(strlen(arg), colormode);
	char *buf = calloc(bufsz, sizeof(char));
	
	if(use_utf8)
		ranebo_utf8(buf, arg, colormode);
	else
		ranebo(buf, arg, colormode);
	
	printf("%s%s", buf, separator);
	
	free(buf);
	
	return 0;
}


int main(int argc, const char *const *const argv)
{
	/*int iz = is_valid_utf8("Za\xC5\xBC\xC3\xB3\xC5\x82\xC4\x87 G\xC4\x99\xC5\x9Bl\xC4\x85 Ja\xC5\xBA\xC5\x84.\n");
	printf("%d\n", iz);
	return 0;*/
	
	int read_stdin = 0;
	const char *separator = "\n";
	int colormode = 2;
	int use_utf8 = 0;
	
	if(argc == 1)
		return 0;
	else
	{
		int state = 1;
		int i;
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
					colormode = RANEBO_BASIC;
				else if(strcmp("--extended", arg) == 0)
					colormode = RANEBO_EXTENDED;
				else if(strcmp("--truecolor", arg) == 0 || strcmp("--tc", arg) == 0)
					colormode = RANEBO_TRUECOLOR;
				else if(strcmp("--separator", arg) == 0 || strcmp("--sep", arg) == 0)
					state = 10;
				else if(strcmp("--utf8", arg) == 0)
					use_utf8 = 1;
				else if(strcmp("--ascii", arg) == 0)
					use_utf8 = 0;
				else if(strcmp("--stdin", arg) == 0)
					read_stdin = 1;
				else if(strcmp("--", arg) == 0)
					state = 2;
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
							case 'u':
								use_utf8 = 1;
								break;
							case 'a':
								use_utf8 = 0;
								break;
							case 'S':
								read_stdin = 1;
								break;
							default:
								fprintf(stderr, "Invalid flag option: -%c\n", c);
								return 2;
						}
					}
skip_flags:;
				}
				else
				{	/* string */
					int o = print_ranebo_arg(arg, separator, colormode, use_utf8);
					if(o)
						return o;
				}
			} break;
			case 2:
			{	/* only strings */
				int o = print_ranebo_arg(arg, separator, colormode, use_utf8);
				if(o)
					return o;
			} break;
			case 10:
			{	/* separator */
				separator = arg;
				state = 1;
			} break;
			}
		}
	}
	
	if(read_stdin)
	{
		int seplen = strlen(separator);
		int argbufsz = seplen + 1;
		char *argbuf = calloc(seplen + 1, sizeof(char));
		int argbuflen = 0;
		
		int ch;
		while((ch = getchar()) != EOF)
		{
			if(argbufsz == argbuflen)
				argbuf = realloc(argbuf, (argbufsz *= 2) * sizeof(char));
			
			argbuf[argbuflen++] = ch;
			
			if(argbuflen >= seplen && ch == separator[seplen - 1])
			{
				argbuf[argbuflen] = '\0'; /* since this might not be the case after a realloc */
				if(strcmp(argbuf + argbuflen - seplen, separator) == 0)
				{
					argbuf[argbuflen - seplen] = '\0';
					
					int o = print_ranebo_arg(argbuf, separator, colormode, use_utf8);
					if(o)
					{
						free(argbuf);
						return o;
					}
					
					argbuflen = 0;
				}
			}
		}
		
		if(argbuflen > 0)
		{
			argbuf[argbuflen - seplen] = '\0';
			int o = print_ranebo_arg(argbuf, separator, colormode, use_utf8);
			if(o)
			{
				free(argbuf);
				return o;
			}
			argbuflen = 0;
		}
		
		free(argbuf);
	}
	
	return 0;
}
