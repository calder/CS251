#ifndef STATES_H
#define STATES_H

#include <stdbool.h>


/// An NFA state the tokenizer can be in
struct __State
{
    bool accept;
    bool parse;
    const char* type;
    struct __State* (*transition) (char);
}
typedef State;


State start_state;
State bool_hash_state;
State bool_letter_state;
State int_sign_state;
State int_digit_state;
State float_dot_state;
State float_decimal_state;
State string_data_state;
State string_close_state;
State symbol_state;
State openparen_state;
State closeparen_state;
State whitespace_state;
State comment_data_state;
State blockcomment_open_state;
State blockcomment_data_state;
State blockcomment_close1_state;
State blockcomment_close2_state;


#endif