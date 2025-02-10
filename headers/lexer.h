#ifndef LEXER_H
#define LEXER_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct {
  int started_specifier;
  char *input;
  int position;
  int read_pos;
  char ch;
} lexer;

lexer *new_lexer(const char *input);
void lexer_end(lexer *lexer);
void read_char(lexer *lexer);
#endif // !LEXER_H
