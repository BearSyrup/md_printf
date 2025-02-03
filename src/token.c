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
  case ' ':
    strcpy(tk->literal, " ");
    tk->token_type = WORD;
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
    strcpy(tk->literal, strcat(read_word(lexer), "\0"));
    tk->token_type = WORD;
    break;
  }
  return tk;
}

char *read_word(lexer *lexer) {
  int start_pos;
  char *identifier;

  start_pos = lexer->position;
  while (is_letter(lexer->ch)) {
    printf("this is the character: %c at position %d \n", lexer->ch,
           lexer->position);
    read_char(lexer);
  }
  memcpy(identifier, &lexer->input[start_pos], lexer->position - start_pos);
  printf("\nthis is the inicial value: %d\nthis is the position: %d\nthis "
         "is the identifier: %s\n",
         start_pos, lexer->position, identifier);
  return identifier;
}

char *read_specifier(lexer *lexer) {
  int start_pos;
  char *specifier;

  start_pos = lexer->position;
  while (is_specifier(lexer)) {
    read_char(lexer);
  }
  memcpy(specifier, &lexer->input[start_pos], lexer->position - start_pos);
  return specifier;
}
int is_specifier(lexer *lexer) {
  char *ch_pos;
  char *specifiers = "dxXip%";
  int prev_pos;

  prev_pos = lexer->position - 1;
  if (lexer->input[prev_pos] == '%') {
    ch_pos = strchr(specifiers, lexer->ch);
    return ch_pos != NULL;
  }
  return 0;
}

int is_letter(char ch) {
  return ('a' <= ch && ch <= 'z') || ('A' <= ch && ch <= 'Z') && (ch != ' ');
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

void new_list_token(list_token *tkn_list, size_t inicial_size) {
  size_t size = sizeof(token) * inicial_size;
  size_t list_size = sizeof(list_token);

  tkn_list->tokens = malloc(size);
  if (tkn_list->tokens == NULL) {
    printf("fail to alloc mem");
    exit(1);
  }
  tkn_list->used = 0;
  tkn_list->size = inicial_size;
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
void tkn_list_end(list_token *tokens) {
  if (tokens != NULL) {
    if (tokens->tokens != NULL) {
      free(tokens->tokens);
    }
    tokens->tokens = NULL;
    tokens->size = tokens->used = 0;
  }
}
const char *get_token_name(t_token token) {
  switch (token) {
  case START_SPECIFIER:
    return "START";
  case INT_SPECIFIER:
    return "INT";
  case CHAR_SPECIFIER:
    return "CHAR";
  case HEXA_SPECIFIER:
    return "HEXA";
  case POINTER_SPECIFIER:
    return "POINTER";
  case STRING_SPECIFIER:
    return "STRING";
  case PERCENT_SPECIFIER:
    return "PERCENT";
  case ILLEGAL_SPECIFIER:
    return "ILLEGAL";
  case EOF_TOK:
    return "EOF";
  case WORD:
    return "WORD";
  default:
    return "not found";
  };
}
