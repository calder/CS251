#include "Tokenizer/States.h"
#include "Tokenizer/Transitions.h"


#define NA 0

State start_state               = {false, NA,    NA,        &transition_from_start};
// State bool_hash_state           = {false, NA,    NA,        &transition_from_bool_hash};
// State bool_letter_state         = {true,  true,  "boolean", &transition_from_bool_letter};
// State int_sign_state            = {false, NA,    NA,        &transition_from_int_sign};
// State int_digit_state           = {true,  true,  "integer", &transition_from_int_digit};
// State float_dot_state           = {true,  true,  "float",   &transition_from_float_dot};
// State float_decimal_state       = {true,  true,  "float",   &transition_from_float_decimal};
// State string_data_state         = {false, NA,    NA,        &transition_from_string_data};
// State string_close_state        = {true,  true,  "string",  &transition_from_string_close};
// State whitespace_state          = {true,  false, NA,        &transition_from_whitespace};
// State symbol_state              = {true,  true,  "symbol",  &transition_from_symbol};
// State openparen_state           = {true,  true,  "(",       &transition_from_openparen};
// State closeparen_state          = {true,  true,  ")",       &transition_from_closeparen};
// State comment_data_state        = {true,  false, NA,        &transition_from_comment_data};
// State blockcomment_open_state   = {false, NA,    NA,        &transition_from_blockcomment_open};
// State blockcomment_data_state   = {false, NA,    NA,        &transition_from_blockcomment_data};
// State blockcomment_close1_state = {false, NA,    NA,        &transition_from_blockcomment_close1};
// State blockcomment_close2_state = {true,  false, NA,        &transition_from_blockcomment_close2};