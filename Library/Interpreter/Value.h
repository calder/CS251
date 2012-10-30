#ifndef VALUE_H
#define VALUE_H

#include <stdbool.h>
#include "Parser/ParseTree.h"


struct Environment;
struct Value;


/// All first class objects in Scheme
enum
{
    NULL_VALUE,
    BOOLEAN_VALUE,
    FLOAT_VALUE,
    FUNCTION_VALUE,
    INTEGER_VALUE,
    LIST_VALUE,
    STRING_VALUE,
    SYMBOL_VALUE,
}
typedef ValueType;


/// A function and any context necessary to call it
/// @note
///     - <function> is a function pointer to the C function to call.
///     - <environment> is the context in which to evaluate the function.
///     - <parseTree> is the internals of a Scheme lambda expression.  This is
///       unused by all built-in functions.
struct Closure
{
    struct Value* (*function) (struct Closure*,ParseTree*);
    struct Environment* environment;
    int numParams;
    char** params;
    ParseTree* parseTree;
}
typedef Closure;


/// A Scheme cons box
struct List
{
    struct Value* head;
    struct Value* tail;
}
typedef List;


/// A reference counted Scheme first class object
struct Value
{
    int refCount;
    ValueType type;
    union
    {
        bool boolVal;
        float floatVal;
        int intVal;
        char* stringVal;
        char* symbolVal;
        ParseTree* exprVal;
        Closure funcVal;
        List listVal;
    };
}
typedef Value;


/// Malloc and return a new Value with a refCount of 1
Value* value_create (ValueType type);

/// Create a C built-in function
Value* value_create_function (struct Environment* environment, Value*(*func)(Closure*,ParseTree*));

/// Create an empty Scheme list
Value* value_create_list_empty ();

/// Increase a value's refCount by 1
void value_reserve (Value* value);

/// Decrease the value's refCount by 1, and free it if it reaches 0
void value_release (Value* value);

/// Display a value
void value_print (Value* value);


#endif