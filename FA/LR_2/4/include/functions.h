#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>
#include <stdarg.h>

#define MAX_FIB 50

int overfscanf(FILE *stream, const char *format, ...);
int oversscanf(const char *str, const char *format, ...);

int roman_digit_value(char c);
int roman_to_int(const char *s);

unsigned int zeckendorf_to_int(const char *s);

static int str_to_int_base(const char *str, int base, int uppercase);

#endif