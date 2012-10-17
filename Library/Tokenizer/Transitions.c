#include "Tokenizer/States.h"
#include "Tokenizer/Transitions.h"
#include "Util/CharUtil.h"


void transition_from_start (char c, Set* states)
{
    if (c == '(')           { set_add(states, &openparen_state); }
    if (c == ')')           { set_add(states, &closeparen_state); }
    if (c == '#')           { set_add(states, &bool_hash_state); }
    if (c == '"')           { set_add(states, &string_data_state); }
    if (c == ';')           { set_add(states, &comment_data_state); }
    if (c == '|')           { set_add(states, &blockcomment_open_state); }
    if (c == '+')           { set_add(states, &int_sign_state); }
    if (c == '+')           { set_add(states, &float_sign_state); }
    if (c == '-')           { set_add(states, &int_sign_state); }
    if (is_digit(c))        { set_add(states, &int_digit_state); }
    if (is_symbol_start(c)) { set_add(states, &symbol_state); }
    if (is_whitespace(c))   { set_add(states, &whitespace_state); }
}


void transition_from_bool_hash (char c, Set* states)
{
  if ((c == 102) || (c == 116)) { set_add(states, &bool_letter_state); }
}


void transition_from_bool_letter (char c, Set* states)
{
  // Placeholder
}


void transition_from_int_sign (char c, Set* states)
{
  if (is_digit(c)) { set_add(states, &int_digit_state); }
}


void transition_from_int_digit (char c, Set* states)
{
  if (is_digit(c)) { set_add(states, &int_digit_state); }
  if (c == 46)     { set_add(states, &float_dot_state); }
}


void transition_from_float_dot (char c, Set* states)
{
  if (is_digit(c)) { set_add(states, &float_decimal_state); }
}


void transition_from_symbol (char c, Set* states)
{
    if (is_digit(c))       { set_add(states, &symbol_state); }
    if (is_symbol_body(c)) { set_add(states, &symbol_state); }
}


void transition_from_openparen (char c, Set* states) 
{
    // Placeholder
}


void transition_from_closeparen (char c, Set* states)
{
    // Placeholder
}


void transition_from_comment_data (char c, Set* states)
{
    if (c != '\n')  { set_add(states, &comment_data_state); }
}
