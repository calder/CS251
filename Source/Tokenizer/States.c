#include "Tokenizer/States.h"
#include "Tokenizer/Transitions.h"


#define NA 0

State start_state                = {false, NA,    &transition_from_start};
// State bool_hash_state            = {false, NA,    &transition_from_bool_hash};
// State bool_letter_state          = {true,  true,  &transition_from_bool_letter};
// State int_sign_state             = {false, NA,    &transition_from_int_sign};
// State int_digits_state           = {true,  true,  &transition_from_int_digits};
// State float_sign_state           = {false, NA,    &transition_from_float_sign};
// State float_digits_state         = {true,  true,  &transition_from_float_digits};
// State float_dot_state            = {true,  true,  &transition_from_float_dot};
// State float_decimals_state       = {true,  true,  &transition_from_float_decimals};
// State string_open_state          = {false, NA,    &transition_from_string_open};
// State string_data_state          = {false, NA,    &transition_from_string_data};
// State string_close_state         = {true,  true,  &transition_from_string_close};
// State whitespace_state           = {true,  false, &transition_from_whitespace};
// State symbol_start_state         = {true,  true,  &transition_from_symbol_start};
// State symbol_continuation_state  = {true,  true,  &transition_from_symbol_continuation};
// State openparen_state            = {true,  true,  &transition_from_openparen};
// State closeparen_state           = {true,  true,  &transition_from_closeparen};
// State comment_open_state         = {true,  false, &transition_from_comment_open};
// State comment_data_state         = {true,  false, &transition_from_comment_data};
// State blockcomment_open1_state   = {false, NA,    &transition_from_blockcomment_open1};
// State blockcomment_open2_state   = {false, NA,    &transition_from_blockcomment_open1};
// State blockcomment_data_state    = {false, NA,    &transition_from_blockcomment_data};
// State blockcomment_close1_state  = {false, NA,    &transition_from_blockcomment_close1};
// State blockcomment_close2_state  = {true,  false, &transition_from_blockcomment_close2};