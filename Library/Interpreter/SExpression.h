#ifndef SEXPRESSION_H
#define SEXPRESSION_H

#include <stdbool.h>
#include "Interpreter/Closure.h"


/// All types of Scheme expressions
/// So you can sexpress yourself however your heart desires.
enum
{
    BOOLEAN_SEXPRESSION,
    FLOAT_SEXPRESSION,
    INTEGER_SEXPRESSION,
    LAMBDA_SEXPRESSION,
    STRING_SEXPRESSION,
    SYMBOL_SEXPRESSION,
}
typedef SExpressionType;


/// Any already evaluated Scheme expression
struct 
{
    SExpressionType type;
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
typedef SExpression;


/// Malloc and return a new SExpression of the given type
SExpression* sexpression_create (SExpressionType type);

/// Free all memory associated with a SExpression
//
void sexpression_free (SExpression* sexpression);

/// Display a SExpression
void sexpression_print (SExpression* sexpression);


#endif