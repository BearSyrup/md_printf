#include "../headers/lexer.h"
#include "../headers/token.h"
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#define EXIT_SUCCESS 0

int md_printf(const char *str, ...);

int md_printf(const char *str, ...) {
  lexer *ptrlexer;
  token *token_name;
  int str_size = strlen(str);
  token *current_tkn;
  size_t inicial_size = 5;
  list_token tokens;
  va_list args;
  int i;

  /*init objects */
  va_start(args, str);
  ptrlexer = new_lexer(str);
  new_list_token(&tokens, inicial_size);
  current_tkn = next_token(ptrlexer);
  /* TODO: save eof token */
  while (current_tkn->token_type != EOF_TOK) {
    add_token(&tokens, current_tkn);
    current_tkn = next_token(ptrlexer);
  }
  printf("those are the literals:\n");
  for (i = 0; i < 7; i++) {
    printf(" %s:%s, ", tokens.tokens[i]->literal,
           get_token_name(tokens.tokens[i]->token_type));
  }
  printf("\n%s", ptrlexer->input);
  va_end(args);
  lexer_end(ptrlexer);
  tkn_list_end(&tokens);
  return str_size;
}

int main(void) {
  md_printf("this %d is a crazy ideia");
  return EXIT_SUCCESS;
}
