#include "utf8utils.h"

int codepoint_len(char start)
{
	/* 11110xxx */
	if((start & '\xF8') == '\xF0')
		return 4;
	
	/* 1110xxxx */
	if((start & '\xF0') == '\xE0')
		return 3;
	
	/* 110xxxxx */
	if((start & '\xE0') == '\xC0')
		return 2;
	
	/* 0xxxxxxx */
	if((start & '\x80') == '\0')
		return 1;
	
	return 0;
}

int strlen_utf8(const char *str)
{
	int cnt = 0;
	const char *sptr = str;
	char c;
	while((c = *sptr) != '\0')
	{
		int cplen = codepoint_len(c);
		
		sptr += cplen;
		++cnt;
	}
	
	return cnt;
}

int is_valid_utf8(const char *str)
{
	const char *sptr = str;
	char c;
	int cplen = 0, cplencnt = 0;
	while((c = *(sptr++)) != '\0')
	{
		if(cplencnt == 0)
		{
			switch(cplen)
			{
			case 0: break;
			case 1: break;
			case 2:
			{
				long byte0 = sptr[-3] & '\x1F';
				long byte1 = sptr[-2] & '\x3F';
				long codepoint = byte0 << 6 | byte1;
				if(codepoint < 0x0080L || codepoint > 0x07FFL)
					return 0;
			} break;
			case 3:
			{
				long byte0 = sptr[-4] & '\x0F';
				long byte1 = sptr[-3] & '\x3F';
				long byte2 = sptr[-2] & '\x3F';
				long codepoint = byte0 << 12 | byte1 << 6 | byte2;
				if(codepoint < 0x0800L || codepoint > 0xFFFFL)
					return 0;
			} break;
			case 4:
			{
				long byte0 = sptr[-5] & '\x07';
				long byte1 = sptr[-4] & '\x3F';
				long byte2 = sptr[-3] & '\x3F';
				long byte3 = sptr[-2] & '\x3F';
				long codepoint = byte0 << 18 | byte1 << 12 | byte2 << 6 | byte3;
				if(codepoint < 0x10000L || codepoint > 0x10FFFFL)
					return 0;
			} break;
			}
			cplencnt = cplen = codepoint_len(c);
		}
		
		if(cplen == 0)
			return 0;
		
		--cplencnt;
	}
	
	if(cplencnt == 0)
		return 1;
	else
		return 0;
}
