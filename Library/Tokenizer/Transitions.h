#ifndef TRANSITIONS_H
#define TRANSITIONS_H

#include "Util/Set.h"

// Michael--you can make Carissa do some of these
// because she feels bad now that she's not doing
// the block comment stuff
void transition_from_start (char c, Set* states);
void transition_from_bool_hash (char c, Set* states);
void transition_from_bool_letter (char c, Set* states);
void transition_from_int_sign (char c, Set* states);
void transition_from_int_digit (char c, Set* states);
void transition_from_float_sign (char c, Set* states);
void transition_from_float_digit (char c, Set* states);
void transition_from_float_dot (char c, Set* states);
void transition_from_float_decimal (char c, Set* states);
void transition_from_string_data (char c, Set* states);
void transition_from_string_close (char c, Set* states);
void transition_from_whitespace (char c, Set* states);


// Carissa
void transition_from_symbol (char c, Set* states);
void transition_from_openparen (char c, Set* states);
void transition_from_closeparen (char c, Set* states);
void transition_from_comment_open (char c, Set* states);
void transition_from_comment_data (char c, Set* states);


#endif
