#ifndef STATES_H
#define STATES_H

#include <stdbool.h>
#include "Util/Set.h"


/// A NFA-style state of the tokenizer
struct
{
    bool accept;
    bool parse;
    void (*transition) (char, Set*);
}
typedef State;


State start_state;
State bool_hash_state;
State bool_hash_state;
State bool_letter_state;
State int_sign_state;
State int_digits_state;
State float_sign_state;
State float_digits_state;
State float_dot_state;
State float_decimals_state;
State string_open_state;
State string_data_state;
State string_close_state;
State whitespace_state;
State symbol_start_state;
State symbol_continuation_state;
State openparen_state;
State closeparen_state;
State comment_open_state;
State comment_data_state;
State blockcomment_open1_state;
State blockcomment_open2_state;
State blockcomment_data_state;
State blockcomment_close1_state;
State blockcomment_close2_state;


#endif