#ifndef LEXER_H
#define LEXER_H
typedef struct {
  char *input;
  int position;
  int read_pos;
  char ch;
} lexer;

lexer *new_lexer(const char *input);
void lexer_end(lexer *lexer);
void read_char(lexer *lexer);
#endif // !LEXER_H
