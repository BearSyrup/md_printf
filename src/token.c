#include "../headers/token.h"
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
    // new one
    strcpy(tk->literal, "%");
    tk->token_type = START_SPECIFIER;
    lexer->started_specifier = 1;
    break;
  default:

    if (lexer->started_specifier) {
      /*TODO: start here; -> read specifier and flags -> generate list of tokens
       * -> send to parser -> idunno */
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
  int word_size;

  start_pos = lexer->position;
  while (is_letter(lexer->ch)) {
    read_char(lexer);
  }

  word_size = lexer->position - start_pos;
  identifier = malloc(sizeof(char) * (word_size + 1));
  memcpy(identifier, &lexer->input[start_pos], word_size);

  return identifier;
}

char *read_specifier(lexer *lexer) {
  int start_pos;
  char *specifier;

  start_pos = lexer->position;
  while (is_specifier(lexer->ch)) {
    read_char(lexer);
  }
  memcpy(specifier, &lexer->input[start_pos], lexer->position - start_pos);
  return specifier;
}
int is_flag(char ch_identifier) {
  // Flags => '-' to justify
  // Flags => '+' to print positive or negative (even for positives)
  // Flags => 'space' space for positive numbes  but does nothing for negative
  // ones Flags => o padding with zeros number of zeros come after Flags => #
  // adds output format for certain conventions e.g %#o 0123 for octal numbers |
  // %#x or %#X 0x48b or 0x48B
  char *ch_pos;
  const char *flags = "-+0#";
  int is_number = ch_identifier >= '0' && '9' >= ch_identifier;
  ch_pos = strchr(flags, ch_identifier);

  return ch_pos != NULL || is_number;
}

t_token get_flag_token(char ch) {
  switch (ch) {
  case '#':
    return ALTERNATE_FORM;
  case '-':
    return LEFT_JUSTIFY_FLAG;
  case '+':
    return FORCE_SIGN_FLAG;
  case ' ':
    return SPACE_FLAG;
  case '0':
    return ZERO_PADDING;
  }
}

int is_specifier(char ch) {
  char *ch_pos;
  const char specifiers[] = {'s', 'c', 'd', 'x', 'X', 'i', 'p', '%'};
  ch_pos = strchr(specifiers, ch);

  return ch_pos != NULL;
}
/* TODO: DELETE*/
int is_old_specifier(lexer *lexer) {
  char *ch_pos;
  int prev_pos;
  int is_specifier_flag;
  int is_number;

  const char specifiers[] = {'s', 'c', 'd', 'x', 'X', 'i', 'p',
                             '%', '-', '+', '0', '#', ' '};

  is_specifier_flag = lexer->input[prev_pos] == '%';
  is_number = lexer->ch >= '0' && lexer->ch <= '9';
  prev_pos = lexer->position - 1;

  if (is_specifier_flag || (is_specifier_flag && is_number)) {
    ch_pos = strchr(specifiers, lexer->ch);
    return ch_pos != NULL || is_number;
  }
  return 0;
}

int is_letter(char ch) {
  return (('a' <= ch && ch <= 'z') || ('A' <= ch && ch <= 'Z')) ||
         (ch == ',') && (ch != ' ');
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
  case 'c':
    return CHAR_SPECIFIER;
  case 's':
    return STRING_SPECIFIER;
  case '%':
    return PERCENT_SPECIFIER;
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
void get_tokens_from_specifier(list_token **tokens, char *token_literal) {
  int i;
  i = 0;
  while (token_literal[i++]) {
    /* flag width precision length specifier */
    if (is_flag(token_literal[i])) {
      get_flag_token(token_literal[i]);

    } else if (is_specifier(token_literal[i])) {
      continue;
    }
  }
}

list_token *get_tokens(lexer *lexer) {
  size_t inicial_list_size = 5;
  list_token *tokens;
  token *current_tkn;
  new_list_token(tokens, inicial_list_size);

  current_tkn = next_token(lexer);
  while (current_tkn->token_type != EOF_TOK) {
    if (current_tkn->token_type == START_SPECIFIER) {
      get_tokens_from_specifier(tokens, current_tkn->literal);
      continue;
    }
    add_token(tokens, current_tkn);
    current_tkn = next_token(lexer);
  }
  // while (current_tkn->token_type != EOF_TOK) {
  //   add_token(&tokens, current_tkn);
  //   current_tkn = next_token(ptrlexer);
  // }
  return tokens;
}
