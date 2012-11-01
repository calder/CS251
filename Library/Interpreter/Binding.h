#ifndef BINDING_H
#define BINDING_H

#include "Tokenizer/Value.h"


/// A symbol and the value it is set to
/// @note Bindings are not reference counted themselves, but they reserve
/// the Value they are using until they are freed.
struct
{
    char* symbol;
    Value* value;
}
typedef Binding;


/// Malloc and return a new Binding, and reserve its Value
Binding* binding_create (const char* symbol, Value* value);

/// Free a Binding and release it's Value
void binding_free (Binding* binding);

/// Display a Binding as "SYMBOL:VALUE "
void binding_print (Binding* binding);

/// Change the Value bound to this symbol
void binding_set (Binding* binding, Value* value);


#endif