#include "../headers/parser.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>

void evaluate(list_token *tokens, va_list list_va) {
  size_t i;
  int j;
  int int_value;
  char *ascii_values;
  char *str;
  uintptr_t ptr_value;
  int has_signal_space = 0; // space flag put space before positive numbers
  int future = 0;
  int width = 0;
  char zero = '0';

  for (i = 0; i < tokens->used; i++) {
    char *literal = tokens->tokens[i]->literal;
    t_token type_token = tokens->tokens[i]->token_type;
    switch (type_token) {
    case WORD:
      mk_puts(literal);
      break;
    case START_SPECIFIER:
      break;
    case INT_SPECIFIER:
      int_value = va_arg(list_va, int);
      if (has_signal_space && int_value < 0) {
        putchar(' ');
      }
      ascii_values = itoa(int_value, ascii_values, 10);
      mk_puts(ascii_values);
      break;
    case CHAR_SPECIFIER:
      int_value = va_arg(list_va, int);
      write(1, &int_value, sizeof(char));
      break;
    case HEXA_SPECIFIER:
      int_value = va_arg(list_va, int);
      ascii_values = itoa(int_value, ascii_values, 16);
      mk_puts(ascii_values);
      break;
    case POINTER_SPECIFIER:
      /* TODO: get right information and format output pointer */
      ptr_value = va_arg(list_va, uintptr_t);
      ascii_values = itoa(ptr_value, ascii_values, 16);
      mk_puts(ascii_values);
      break;
    case STRING_SPECIFIER:
      str = va_arg(list_va, char *);
      mk_puts(str);
      break;
    case PERCENT_SPECIFIER:
      break;
    case ILLEGAL_SPECIFIER:
      puts("Illegal specifier... exiting");
      exit(0);
    case EOF_TOK:
      putchar(' ');
      break;
    case LEFT_JUSTIFY_FLAG:
    case FORCE_SIGN_FLAG:
    case SPACE_FLAG:
      has_signal_space = 1;
      break;
    case ZERO_PADDING:
      future = i;
      while (tokens->tokens[future]->token_type != WIDTH) {
        future++;
      }
      width = mk_atoi(tokens->tokens[future]->literal);
      for (int n = 0; n < width; n++) {
        write(1, &zero, 1);
      }

      break;
    case ALTERNATE_FORM:
      break;
    case LENGTH:
    case PRECISION:
    case WIDTH:
      break;
    }
  }
}
