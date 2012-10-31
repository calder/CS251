#ifndef VALUEUTIL_H
#define VALUEUTIL_H

#include "Tokenizer/Tokens.h"


void check_bool_value   (Value* value, bool  boolVal);
void check_float_value  (Value* value, float floatVal);
void check_int_value    (Value* value, int   intVal);
void check_lambda_value (Value* value);
void check_list_value   (Value* value);
void check_string_value (Value* value, char* stringVal);
void check_symbol_value (Value* value, char* symbolVal);


#endif