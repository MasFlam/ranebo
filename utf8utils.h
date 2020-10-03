#ifndef RANEBO_UTF8_UTILS_H
#define RANEBO_UTF8_UTILS_H


/* Returns the length of the codepoint starting with start,
 * or 0 if no valid codepoint can start with start.
*/
int codepoint_len(char start);

/* Returns the number of UTF-8 codepoints in the given string.
 * If the string is not null-terminated, the behavior is undefined.
*/
int strlen_utf8(const char *string);

/* Returns 1 if the given string is valid UTF-8, 0 otherwise.
 * If the string is not null-terminated, the behavior is undefined.
*/
int is_valid_utf8(const char *string);


#endif
