#ifndef PARSER_H
#define PARSER_H
#include "mikastd.h"
#include "token.h"
#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
void evaluate(list_token *tokens, va_list);

#endif // !PARSER_H
