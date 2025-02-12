#include "../headers/lexer.h"

char peek(const lexer *l) { return l->input[l->position]; }

void read_char(lexer *lexer) {
  if (lexer->read_pos >= strlen(lexer->input)) {
    lexer->ch = 0;
  } else {
    lexer->ch = lexer->input[lexer->read_pos];
  }
  lexer->position = lexer->read_pos;
  lexer->read_pos += 1;
}

char *read_word(lexer *lexer) {
  int start_pos;
  char *identifier;
  int word_size;

  start_pos = lexer->position;
  while (is_alpha(lexer->ch)) {
    read_char(lexer);
  }
  word_size = lexer->position - start_pos;
  identifier = malloc(sizeof(char) * (word_size + 1));
  memcpy(identifier, &lexer->input[start_pos], word_size);

  return identifier;
}

char *read_specifier(lexer *lexer) {
  int start_pos;
  char *specifier;

  start_pos = lexer->position;
  while (is_special_char(lexer->ch) && lexer->ch) {
    read_char(lexer);
  }
  specifier = malloc(sizeof(char) * ((lexer->position - start_pos) + 1));
  memcpy(specifier, &lexer->input[start_pos], lexer->position - start_pos);
  return specifier;
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
