#ifndef MD_PRINTF_H
#define MD_PRINTF_H

#include "../headers/lexer.h"
#include "../headers/parser.h"
#include "../headers/token.h"
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#define EXIT_SUCCESS 0

int md_printf(const char *str, ...);

#endif // MD_PRINTF_H
