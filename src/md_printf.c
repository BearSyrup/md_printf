#include "../headers/lexer.h"
#include "../headers/token.h"
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#define EXIT_SUCCESS 0

int mk_printf(const char *str, ...);

int mk_printf(const char *str, ...) {
  lexer *ptrlexer;
  token *token_name;
  int str_size = strlen(str);

  va_list args;
  va_start(args, str);

  ptrlexer = new_lexer(str);
  token_name = next_token(ptrlexer);
  if (token_name->token_type == INT) {
    printf("we got the token and the value is: %d", va_arg(args, int));
  }
  va_end(args);
  lexer_end(ptrlexer);
  return str_size;
}

int main(void) {
  lexer *ptrlexer;
  char test_token[10] = "%d this is";
  token *tk_test;

  ptrlexer = new_lexer(test_token);
  tk_test = next_token(ptrlexer);

  putchar(ptrlexer->ch);
  putchar('\n');

  printf("starting test\n");

  mk_printf("%d", 2);
  return EXIT_SUCCESS;
}
