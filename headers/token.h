#ifndef TOKEN_H
#define TOKEN_H
#include "lexer.h"

/* d: inteder i: interger p: pointer s:string c: char xX: hexadecimal %%
 * character: %*/
typedef enum {
  STRT_SPECIFIER,
  INT,
  CHAR,
  HEXA,
  POINTER,
  STRING,
  PERCENT,
  ILLEGAL,
  EOF_TOK,
  WORD
} t_token;
typedef struct {
  t_token token_type;
  char *literal;
} token;
token *next_token(lexer *lexer);
int is_letter(char ch);
int is_arg_type(char ch);
t_token lookup_identifier(char *identifier);
char *read_tok(lexer *lexer);
char *read_identifier(lexer *lexer);

#endif
