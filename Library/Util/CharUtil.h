#ifndef CHARUTIL_H
#define CHARUTIL_H

#include <stdbool.h>


bool is_digit (char c);

bool is_finalizer (char c);

bool is_letter (char c);

bool is_paren (char c);

bool is_symbol_start (char c);

bool is_symbol_body (char c);

bool is_whitespace (char c);


#endif