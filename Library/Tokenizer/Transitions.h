#ifndef TRANSITIONS_H
#define TRANSITIONS_H


State* transition_from_start (char c);
State* transition_from_bool_hash (char c);
State* transition_from_bool_letter (char c);
State* transition_from_int_sign (char c);
State* transition_from_int_digit (char c);
State* transition_from_float_dot (char c);
State* transition_from_float_decimal (char c);
State* transition_from_string_data (char c);
State* transition_from_string_close (char c);
State* transition_from_whitespace (char c);
State* transition_from_symbol (char c);
State* transition_from_openparen (char c);
State* transition_from_closeparen (char c);
State* transition_from_comment_data (char c);


#endif