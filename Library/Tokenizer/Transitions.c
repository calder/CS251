#include "Tokenizer/States.h"
#include "Tokenizer/Transitions.h"
#include "Util/CharUtil.h"


void transition_from_start (char c, Set* states)
{
    if (c == '(')           { set_add(states, &openparen_state); }
    if (c == ')')           { set_add(states, &closeparen_state); }
    if (c == '#')           { set_add(states, &bool_hash_state); }
    if (c == '"')           { set_add(states, &string_data_state); }
    if (c == ';')           { set_add(states, &string_close_state); }
    if (c == '|')           { set_add(states, &blockcomment_open_state); }
    if (c == '+')           { set_add(states, &int_sign_state); }
    if (c == '+')           { set_add(states, &float_sign_state); }
    if (c == '-')           { set_add(states, &int_sign_state); }
    if (c == '-')           { set_add(states, &float_sign_state); }
    if (is_digit(c))        { set_add(states, &int_digit_state); }
    if (is_digit(c))        { set_add(states, &float_digit_state); }
    if (is_symbol_start(c)) { set_add(states, &symbol_state); }
    if (is_whitespace(c))   { set_add(states, &whitespace_state); }
}

// Carissa
void transition_from_symbol (char c, Set* states)
{
    if (is_digit(c))             { set_add(states, &symbol_state); }
    if (is_symbol_subsequent(c)) { set_add(states, &symbol_state); }
}

void transition_from_openparen (char c, Set* states) 
{
    
}

void transition_from_closeparen (char c, Set* states)
{
    
}

void transition_from_comment_open (char c, Set* states)
{
    if (c != '\n')  { set_add(states, &comment_data_state); }
}

void transition_from_comment_data (char c, Set* states)
{
    if (c != '\n')  { set_add(states, &comment_data_state); }
}
