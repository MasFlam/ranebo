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

int is_valid_codepoint(const char *sptr, int cplen)
{
	long codepoint;
	switch(cplen)
	{
	case 2:
	{
		long byte0 = sptr[-3] & '\x1F';
		long byte1 = sptr[-2] & '\x3F';
		codepoint = byte0 << 6 | byte1;
		if(codepoint < 0x0080L || codepoint > 0x07FFL)
			return 1;
	} break;
	case 3:
	{
		long byte0 = sptr[-4] & '\x0F';
		long byte1 = sptr[-3] & '\x3F';
		long byte2 = sptr[-2] & '\x3F';
		codepoint = byte0 << 12 | byte1 << 6 | byte2;
		if(codepoint < 0x0800L || codepoint > 0xFFFFL)
			return 1;
	} break;
	case 4:
	{
		long byte0 = sptr[-5] & '\x07';
		long byte1 = sptr[-4] & '\x3F';
		long byte2 = sptr[-3] & '\x3F';
		long byte3 = sptr[-2] & '\x3F';
		codepoint = byte0 << 18 | byte1 << 12 | byte2 << 6 | byte3;
		if(codepoint < 0x10000L || codepoint > 0x10FFFFL)
			return 1;
	} break;
	}
	
	return 0xD800L <= codepoint && codepoint <= 0xDFFFL;
}

int is_valid_utf8(const char *str)
{
	const char *sptr = str;
	int cplen = 0, cplencnt = 0;
	char c;
	while((c = *(sptr++)) != '\0')
	{
		/* if not on a continuation byte */
		if(cplencnt == 0)
		{
			/* and not at the beginning of the string */
			if(sptr != str + 1 && is_valid_codepoint(sptr, cplen))
				return 0;
			/* if all good, start processing another codepoint */
			cplencnt = cplen = codepoint_len(c);
		}
		/* check if valid continuation byte (10xxxxxx) */
		else if((c & '\xC0') != '\x80')
			return 0;
		
		/* was that a valid codepoint start? */
		if(cplen == 0)
			return 0;
		
		--cplencnt;
	}
	
	/* has the last codepoint ended? */
	if(cplencnt == 0)
	{
		/* valid if empty */
		if(sptr == str + 1)
			return 1;
		/* check if last is good */
		else return !is_valid_codepoint(sptr, cplen);
	}
	else
		return 0;
}
