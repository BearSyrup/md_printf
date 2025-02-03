#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../headers/lexer.h"

void read_char(lexer *lexer) {
  if (lexer->read_pos >= strlen(lexer->input)) {
    lexer->ch = 0;
  } else {
    lexer->ch = lexer->input[lexer->read_pos];
  }
  lexer->position = lexer->read_pos;
  lexer->read_pos += 1;
}

lexer *new_lexer(const char *input) {
  lexer *l;
  size_t input_size;

  l = malloc(sizeof(lexer));
  if (l == 0) {
    puts("fail to alloc mem");
    exit(1);
  }

  input_size = strlen(input);
  l->input = malloc(input_size + 1);
  if (l->input == NULL) {
    puts("fail to alloc mem");
    exit(1);
  }
  strcpy(l->input, input);
  l->input[input_size + 1] = '\0';

  l->position = 0;
  l->read_pos = 0;
  l->ch = 0;

  return l;
}

void lexer_end(lexer *lexer) {
  if (lexer != NULL) {
    free(lexer->input);
    free(lexer);
    lexer = NULL;
  }
}
