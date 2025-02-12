#include "../headers/md_printf.h"

int md_printf(const char *str, ...) {
  lexer *ptrlexer;
  token *token_name;
  int str_size = strlen(str);
  size_t inicial_size = 5;
  list_token *tokens;
  va_list args;
  int i;

  /*init objects */
  va_start(args, str);

  ptrlexer = new_lexer(str);
  tokens = get_tokens(ptrlexer);
  for (int n = 0; n < tokens->used; n++) {
    printf("token[%d] => %s\n", n, tokens->tokens[n]->literal);
  }
  evaluate(tokens, args);

  // Dealocate
  va_end(args);
  lexer_end(ptrlexer);
  tkn_list_end(tokens);
  return str_size;
}

int main(void) {
  md_printf("this is the new test %010d", 23);
  return EXIT_SUCCESS;
}
