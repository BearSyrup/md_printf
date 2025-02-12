#ifndef MIKASTD
#define MIKASTD
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

int is_flag(char ch_identifier);
int mk_is_number(char ch);
int is_special_char(char ch);
char *itoa(int value, char *string, int radix);
void add_char(char *s, char c);
int is_alpha(char ch);
int is_specifier(char ch);
void mk_puts(char *s);
int mk_atoi(const char *strg);
#endif // !MIKASTD
