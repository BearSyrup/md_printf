#ifndef TOKEN_H
#define TOKEN_H
#include "lexer.h"
#include <stddef.h>

/* d: inteder i: interger p: pointer s:string c: char xX: hexadecimal %%
 * character: %*/
typedef enum {
  START_SPECIFIER,
  INT_SPECIFIER,
  CHAR_SPECIFIER,
  HEXA_SPECIFIER,
  POINTER_SPECIFIER,
  STRING_SPECIFIER,
  PERCENT_SPECIFIER,
  ILLEGAL_SPECIFIER,
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
int is_letter(char ch);
int is_specifier(lexer *lexer);
t_token t_token_from_specifier(char specifier);
char *read_specifier(lexer *lexer);
char *read_word(lexer *lexer);
void new_list_token(list_token *tkn_list, size_t inicial_size);
void tkn_list_end(list_token *);
void add_token(list_token *tokens, token *tkn);

#endif
