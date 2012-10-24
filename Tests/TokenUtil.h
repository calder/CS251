#ifndef TOKENUTIL_H
#define TOKENUTIL_H

#include "Tokenizer/Tokens.h"


void check_bool   (Token* token, bool  value);
void check_float  (Token* token, float value);
void check_int    (Token* token, int   value);
void check_paren  (Token* token, char  value);
void check_string (Token* token, char* value);
void check_symbol (Token* token, char* value);


void check_and_free_bool   (Token* token, bool  value);
void check_and_free_float  (Token* token, float value);
void check_and_free_int    (Token* token, int   value);
void check_and_free_paren  (Token* token, char  value);
void check_and_free_string (Token* token, char* value);
void check_and_free_symbol (Token* token, char* value);


#endif