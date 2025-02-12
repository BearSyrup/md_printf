#ifndef LEXER_H
#define LEXER_H
#include "mikastd.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  char *input;
  int position;
  int read_pos;
  char ch;
} lexer;

lexer *new_lexer(const char *input);
char *read_word(lexer *lexer);
char *read_specifier(lexer *lexer);
char peek(const lexer *l);
void lexer_end(lexer *lexer);
void read_char(lexer *lexer);
#endif // !LEXER_H
