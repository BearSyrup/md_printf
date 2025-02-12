#include "../headers/token.h"
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

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
    strcpy(tk->literal, strcat(read_specifier(lexer), "\0"));
    tk->token_type = START_SPECIFIER;
    break;
  default:
    strcpy(tk->literal, strcat(read_word(lexer), "\0"));
    tk->token_type = WORD;
    break;
  }
  return tk;
}

t_token t_token_from_literal(char literal) {
  switch (literal) {
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
  case 'c':
    return CHAR_SPECIFIER;
  case 's':
    return STRING_SPECIFIER;
  case '%':
    return PERCENT_SPECIFIER;
  case '#':
    return ALTERNATE_FORM;
  case '-':
    return LEFT_JUSTIFY_FLAG;
  case '+':
    return FORCE_SIGN_FLAG;
  case 32:
    return SPACE_FLAG;
  case '0':
    return ZERO_PADDING;
  default:
    return ILLEGAL_SPECIFIER;
  }
}

void new_list_token(list_token *tkn_list, size_t inicial_size) {
  size_t size = sizeof(token) * inicial_size;
  size_t list_size = sizeof(list_token);

  tkn_list->tokens = malloc(size);
  if (tkn_list->tokens == NULL) {
    puts("fail to alloc mem");
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
void get_tokens_from_specifier(list_token *tokens, char *token_literal) {
  int i, begin, end;
  token *token;

  i = 1; /* jump % START_SPECIFIER */
  while (token_literal[i] != '\0') {
    /* flag width precision length specifier */
    if (is_flag(token_literal[i])) {
      token = get_flag_token(token_literal[i]);
      add_token(tokens, get_flag_token(token_literal[i]));
    } else if (mk_is_number(token_literal[i])) {
      begin = end = i;
      while (mk_is_number(token_literal[end])) {
        end++;
      }
      i += (end - begin) - 1;
      add_token(tokens, get_width_token(token_literal, begin, end));
    } else if (is_specifier(token_literal[i])) {
      add_token(tokens, get_specifier_token(token_literal[i]));
    }
    i++;
  }
}

token *get_length_token(char ch_length) {
  token *token;
  char s[2] = "";
  token->literal = malloc(sizeof(char) * 2);
  add_char(s, ch_length);
  memcpy(token->literal, s, sizeof(char));
  token->token_type = LENGTH;
  return token;
}

token *get_specifier_token(char ch_specifier) {
  token *ptrtoken;
  ptrtoken = malloc(sizeof(token));
  char s[2] = "";
  ptrtoken->literal = malloc(sizeof(char) * 2);
  add_char(s, ch_specifier);
  memcpy(ptrtoken->literal, s, sizeof(char));
  ptrtoken->token_type = t_token_from_literal(ch_specifier);
  return ptrtoken;
}

token *get_precision_token(char ch_precision) {
  token *ptrtoken;
  ptrtoken = malloc(sizeof(token));
  char s[2] = "";
  ptrtoken->literal = malloc(sizeof(char) * 2);
  add_char(s, ch_precision);
  memcpy(ptrtoken->literal, s, sizeof(char));
  ptrtoken->token_type = PRECISION;
  return ptrtoken;
}

token *get_flag_token(char ch_flag) {
  token *ptrtoken;
  ptrtoken = malloc(sizeof(token));
  ptrtoken->literal = malloc(sizeof(char) * 2);
  char s[2] = "";
  add_char(s, ch_flag);
  memcpy(ptrtoken->literal, s, sizeof(char));
  ptrtoken->token_type = t_token_from_literal(ch_flag);
  return ptrtoken;
}

token *get_width_token(char *token_literal, int begin_str, int end_str) {
  token *ptrtoken;
  ptrtoken = malloc(sizeof(token));
  ptrtoken->literal = malloc((end_str - begin_str) * sizeof(char));
  memcpy(ptrtoken->literal, &token_literal[begin_str], end_str - begin_str);
  ptrtoken->token_type = WIDTH;
  return ptrtoken;
}

list_token *get_tokens(lexer *lexer) {
  size_t inicial_list_size = 5;
  list_token *tokens;
  token *current_tkn;

  tokens = malloc(sizeof(list_token));
  new_list_token(tokens, inicial_list_size);

  current_tkn = next_token(lexer);
  while (current_tkn->token_type != EOF_TOK) {
    if (current_tkn->token_type == START_SPECIFIER) {
      get_tokens_from_specifier(tokens, current_tkn->literal);
      current_tkn = next_token(lexer);
      continue;
    }
    add_token(tokens, current_tkn);
    current_tkn = next_token(lexer);
  }

  return tokens;
}
