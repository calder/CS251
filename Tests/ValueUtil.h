#ifndef VALUEUTIL_H
#define VALUEUTIL_H

#include "Tokenizer/Value.h"


void check_bool   (Value* value, bool  expected);
void check_float  (Value* value, float expected);
void check_int    (Value* value, int   expected);
void check_list   (Value* value);
void check_paren  (Value* value, char  expected);
void check_string (Value* value, char* expected);
void check_symbol (Value* value, char* expected);


void check_and_free_bool   (Value* value, bool  expected);
void check_and_free_float  (Value* value, float expected);
void check_and_free_int    (Value* value, int   expected);
void check_and_free_list   (Value* value);
void check_and_free_paren  (Value* value, char  expected);
void check_and_free_string (Value* value, char* expected);
void check_and_free_symbol (Value* value, char* expected);


#endif