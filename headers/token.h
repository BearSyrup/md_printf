#ifndef TOKEN_H
#define TOKEN_H
#include "lexer.h"
#include "mikastd.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
  START_SPECIFIER,
  LENGTH,
  PRECISION,
  WIDTH,
  INT_SPECIFIER,
  LEFT_JUSTIFY_FLAG,
  FORCE_SIGN_FLAG,
  SPACE_FLAG,
  ZERO_PADDING,
  ALTERNATE_FORM,
  CHAR_SPECIFIER,
  HEXA_SPECIFIER,
  POINTER_SPECIFIER,
  STRING_SPECIFIER,
  PERCENT_SPECIFIER,
  ILLEGAL_SPECIFIER,
  FINISH_SPECIFIER,
  EOF_TOK,
  WORD
} t_token;

typedef struct {
  t_token token_type;
  char *literal;
} token;

typedef struct {
  token **tokens;
  size_t used;
  size_t size;
} list_token;

const char *get_token_name(t_token token);
token *next_token(lexer *lexer);
list_token *get_tokens(lexer *lexer);
t_token t_token_from_literal(char literal);
void new_list_token(list_token *tkn_list, size_t inicial_size);
void tkn_list_end(list_token *);
void add_token(list_token *tokens, token *tkn);
token *get_width_token(char *token_literal, int begin_str, int end_str);
token *get_precision_token(char ch_precision);
token *get_length_token(char ch_length);
token *get_flag_token(char ch_flag);
token *get_specifier_token(char ch_specifier);
#endif
