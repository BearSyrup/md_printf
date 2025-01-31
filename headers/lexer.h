#ifndef LEXER_H
#define LEXER_H
typedef struct {
  char *input;
  int position;
  int read_pos;
  char ch;
} lexer;

lexer *lexer_init(const char *input);
void lexer_end(lexer *lexer);
lexer *tokenize(char *input);
void read_char(lexer *lexer);
#endif // !LEXER_H
