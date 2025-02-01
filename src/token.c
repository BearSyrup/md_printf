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

    /* TODO: start token here -> every letter has to be read diferently from now
     * on */
    strcpy(tk->literal, read_tok(lexer));
    tk->token_type = lookup_identifier(tk->literal);
    break;
  case 'd':

  default:
    strcpy(tk->literal, read_identifier(lexer));
    tk->token_type = WORD;
    break;
  }
  return tk;
}

char *read_identifier(lexer *lexer) {
  int position;
  char *identifier;

  position = lexer->position;

  while (is_letter(lexer->ch)) {
    read_char(lexer);
  }
  memcpy(identifier, &lexer->input[position], lexer->read_pos - position);
  return identifier;
}
char *read_tok(lexer *lexer) {
  int position;
  char *identifier;

  position = lexer->position;
  while (is_specifier(lexer->ch)) {
    read_char(lexer);
  }
  memcpy(identifier, &lexer->input[position], lexer->position - position);
  return identifier;
}
int is_specifier(char ch) {
  char *ch_pos;
  char *specifiers = "dxXip%";
  ch_pos = strchr(specifiers, ch);
  return ch_pos != NULL;
}

int is_letter(char ch) {
  return ('a' <= ch && ch <= 'z') || ('A' <= ch && ch <= 'Z');
}

t_token lookup_identifier(char *identifier) {
  if (strcmp(identifier, "%d")) {
    return INT;
  }
  return ILLEGAL;
}
