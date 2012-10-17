#include <stdlib.h>
#include "Tokenizer/States.h"
#include "Tokenizer/Transitions.h"
#include "Util/CharUtil.h"


State* transition_from_start (char c)
{
    if (c == '(')           { return &openparen_state; }
    if (c == ')')           { return &closeparen_state; }
    if (c == '#')           { return &bool_hash_state; }
    if (c == '"')           { return &string_data_state; }
    if (c == ';')           { return &comment_data_state; }
    if (c == '|')           { return &blockcomment_open_state; }
    if (c == '+')           { return &int_sign_state; }
    if (c == '-')           { return &int_sign_state; }
    if (is_digit(c))        { return &int_digit_state; }
    if (is_symbol_start(c)) { return &symbol_state; }
    if (is_whitespace(c))   { return &whitespace_state; }
    return NULL;
}


State* transition_from_symbol (char c)
{
    if (is_symbol_start(c) || is_digit(c)) { return &symbol_state; }
    return NULL;
}


State* transition_from_openparen (char c) 
{
    return NULL;
}


State* transition_from_closeparen (char c)
{
    return NULL;
}


State* transition_from_comment_data (char c)
{
    if (c != '\n')  { return &comment_data_state; }
    return NULL;
}