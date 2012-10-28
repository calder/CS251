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
    EXPRESSION_VALUE,
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
        List listVal;
        Closure funcVal;
        ParseTree* exprVal;
    };
}
typedef Value;


/// Malloc and return a new Value with a refCount of 1
Value* value_create (ValueType type);

/// Convenience function to create an unevaluated expression
Value* value_create_expression (ParseTree* parseTree);

/// Convenience function to create a C built-in function
Value* value_create_function_builtin (struct Environment* environment, Value*(*func)(Closure*,ParseTree*));

/// Convenience function to create a Scheme lambda expression
Value* value_create_function_scheme (struct Environment* environment, ParseTree* parseTree);

/// Increase a value's refCount by 1
void value_reserve (Value* value);

/// Decrease the value's refCount by 1, and free it if it reaches 0
void value_release (Value* value);

/// Display a value
void value_print (Value* value);


#endif