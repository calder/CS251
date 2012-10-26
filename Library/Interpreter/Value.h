#ifndef VALUE_H
#define VALUE_H

#include <stdbool.h>
#include "Interpreter/Closure.h"


/// All first class objects in Scheme
enum
{
    BOOLEAN_VALUE,
    FLOAT_VALUE,
    INTEGER_VALUE,
    LAMBDA_VALUE,
    STRING_VALUE,
    SYMBOL_VALUE,
}
typedef ValueType;


/// A reference counted Scheme first class object
struct 
{
    int refCount;
    ValueType type;
    union
    {
        bool boolVal;
        float floatVal;
        int intVal;
        Closure lambdaVal;
        char* stringVal;
        char* symbolVal;
    };
}
typedef Value;


/// Malloc and return a new Value with a refCount of 1
Value* value_create (ValueType type);

/// Increase a value's refCount by 1
void value_reserve (Value* value);

/// Decrease the value's refCount by 1, and free it if it reaches 0
void value_release (Value* value);

/// Display a value
void value_print (Value* value);


#endif