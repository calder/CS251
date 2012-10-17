#include "Tokenizer/States.h"
#include "Tokenizer/Tokens.h"
#include "Tokenizer/Transitions.h"


#define NA 0

State start_state               = {false, NA,    NA,               &transition_from_start};
State bool_hash_state           = {false, NA,    NA,               &transition_from_bool_hash};
State bool_letter_state         = {true,  true,  &tokenize_bool,   &transition_from_bool_letter};
State int_sign_state            = {false, NA,    NA,               &transition_from_int_sign};
State int_digit_state           = {true,  true,  &tokenize_int,    &transition_from_int_digit};
State float_dot_state           = {true,  true,  &tokenize_float,  &transition_from_float_dot};
State float_decimal_state       = {true,  true,  &tokenize_float,  &transition_from_float_decimal};
State string_data_state         = {false, NA,    NA,               &transition_from_string_data};
State string_close_state        = {true,  true,  &tokenize_string, &transition_from_string_close};
State whitespace_state          = {true,  false, NA,               &transition_from_whitespace};
State symbol_state              = {true,  true,  &tokenize_symbol, &transition_from_symbol};
State paren_state               = {true,  true,  &tokenize_paren,  &transition_from_paren};
State comment_data_state        = {true,  false, NA,               &transition_from_comment_data};