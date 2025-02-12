#include "../headers/mikastd.h"
#include <string.h>
#include <unistd.h>

void reverse_string(char *string) {
  int left;
  int right;
  char rev_buff;

  left = 0;
  right = strlen(string) - 1;

  while (left < right) {
    rev_buff = string[left];
    string[left] = string[right];
    string[right] = rev_buff;

    left++;
    right--;
  }
}
void add_char(char *s, char c) {
  while (*s++)
    ;

  *(s - 1) = c;
  *s = '\0';
}

int mk_is_number(char ch) {
  int res;

  res = ('0' <= ch) && (ch <= '9');

  return res;
}

int is_flag(char ch_identifier) {
  /* Flags => '-' to justify
   Flags => '+' to print positive or negative (even for positives)
   Flags => 'space' space for positive numbes  but does nothing for negative
   ones Flags => o padding with zeros number of zeros come after Flags => #
   adds output format for certain conventions e.g %#o 0123 for octal numbers
   %#x or %#X 0x48b or 0x48B */

  char *ch_pos;
  const char flags[] = {'-', '+', '0', '#', 32};
  ch_pos = strchr(flags, ch_identifier);

  return ch_pos != NULL;
}

int is_special_char(char ch) {
  char *ch_pos;
  const char specifiers[] = {'s', 'c', 'd', 'x', 'X', 'i', 'p',
                             '%', '-', '+', '0', '#', 32};

  ch_pos = strchr(specifiers, ch);
  int verify = ch_pos != NULL || mk_is_number(ch);
  return verify;
}

int is_alpha(char ch) {
  return (('a' <= ch && ch <= 'z') || ('A' <= ch && ch <= 'Z')) || (ch == ',');
}

int is_specifier(char ch) {
  char *ch_pos;
  const char specifiers[] = {'s', 'c', 'd', 'x', 'X', 'i', 'p', '%'};
  ch_pos = strchr(specifiers, ch);

  return ch_pos != NULL;
}

void mk_puts(char *s) {
  int len;
  int i;
  int space = 32;

  len = strlen(s);

  for (i = 0; i < len; i++) {
    write(1, &s[i], 1);
  }
  write(1, &space, 1);
}

char *itoa(int value, char *string, int radix) {
  int is_negative;
  int remainder;
  char asc_character;
  int i;

  if (value == 0) {
    char *zero_value = "0/0";
    string = malloc(sizeof(char) * strlen(zero_value));
    memcpy(string, zero_value, strlen(zero_value));
    return string;
  }
  string = malloc(sizeof(char) * 16);
  is_negative = 0;
  if (value < 0) {
    is_negative = 1;
  }
  i = 0;
  while (value) {
    remainder = value % radix;
    string[i++] = (remainder > 9) ? (remainder - 10) + 'a' : remainder + '0';
    value /= radix;
  }
  if (is_negative) {
    string[i++] = '-';
  }
  string[i] = '\0';

  reverse_string(string);

  return string;
}
int mk_atoi(const char *strg) {
  int res = 0;
  int i = 0;

  while (strg[i] != '\0') {
    res = res * 10 + (strg[i] - '0');
    i++;
  }
  return res;
}
