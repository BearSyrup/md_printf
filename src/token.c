#include "../headers/token.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

token *next_token(lexer *lexer) {
  token *tk;

  tk = malloc(sizeof(token));
  if (tk == NULL) {
    puts("fail to alloc mem");
    exit(1);
  }
  tk->literal = malloc(strlen(lexer->input));
  if (tk->literal == NULL) {
    puts("fail to alloc mem");
    exit(1);
  }

  read_char(lexer);
  switch (lexer->ch) {
  case '\0':
    tk->literal = 0;
    tk->token_type = EOF_TOK;
    break;
  case '%':
    strcpy(tk->literal, "%");
    tk->token_type = START_SPECIFIER;
    break;
  default:
    if (is_specifier(lexer)) {
      memcpy(tk->literal, &lexer->ch, 1);
      tk->token_type = t_token_from_specifier(lexer->ch);
      break;
    }
    strcpy(tk->literal, read_word(lexer));
    tk->token_type = WORD;
    break;
  }
  return tk;
}

char *read_word(lexer *lexer) {
  int position;
  char *identifier;

  position = lexer->position;

  while (is_letter(lexer->ch)) {
    read_char(lexer);
  }
  memcpy(identifier, &lexer->input[position], lexer->read_pos - position);
  return identifier;
}
char *read_specifier(lexer *lexer) {
  int position;
  char *specifier;

  position = lexer->position;
  while (is_specifier(lexer)) {
    read_char(lexer);
  }
  memcpy(specifier, &lexer->input[position], lexer->position - position);
  return specifier;
}
int is_specifier(lexer *lexer) {
  char *ch_pos;
  char *specifiers = "dxXip%";

  if (lexer->input[lexer->position] == '%') {
    ch_pos = strchr(specifiers, lexer->ch);
  }
  return ch_pos != NULL;
}

int is_letter(char ch) {
  return ('a' <= ch && ch <= 'z') || ('A' <= ch && ch <= 'Z');
}

t_token t_token_from_specifier(char specifier) {
  switch (specifier) {
  case 'd':
    return INT_SPECIFIER;
  case 'i':
    return INT_SPECIFIER;
  case 'p':
    return POINTER_SPECIFIER;
  case 'x':
    return HEXA_SPECIFIER;
  case 'X':
    return HEXA_SPECIFIER;
  default:
    return ILLEGAL_SPECIFIER;
  }
}

void new_list_token(list_token *tokens, size_t inicial_size) {
  size_t size = sizeof(token) * inicial_size;
  size_t list_size = sizeof(list_token);

  tokens = malloc(list_size);
  if (tokens == NULL) {
    printf("fail to alloc mem");
    exit(1);
  }
  tokens->tokens = malloc(size);
  if (tokens->tokens == NULL) {
    printf("fail to alloc mem");
    exit(1);
  }
  tokens->used = 0;
  tokens->size = inicial_size;
}
void add_token(list_token *tokens, token *tkn) {
  size_t token_size;
  size_t increase_factor;

  increase_factor = 3;

  if (tkn != NULL) {
    token_size = sizeof(*tkn);
    if (tokens->used >= tokens->size) {
      tokens->size *= increase_factor;
      tokens->tokens = realloc(tokens->tokens, token_size * (tokens->size));
    }
    tokens->tokens[tokens->used++] = tkn;
  }
}
