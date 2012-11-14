#ifndef VALUES_H
#define VALUES_H

#include <stdbool.h>


struct Environment;
struct ParseTree;


/// All valid types of Scheme values
/// @note Tokens (anything named *_TOKEN) only exist during tokenization and
/// parsing and will never show up during the actual interpretation.  Values
/// (anything of the form *_VALUE) may be created at any point.
enum ValueType
{
    END_TOKEN,
    ERROR_TOKEN,
    NULL_TOKEN,
    PAREN_TOKEN,

    BOOLEAN_VALUE,
    FLOAT_VALUE,
    FUNCTION_VALUE,
    INTEGER_VALUE,
    LAMBDA_VALUE,
    LIST_VALUE,
    NULL_VALUE,
    STRING_VALUE,
    SYMBOL_VALUE,
    UNDEF_VALUE,
}
typedef ValueType;


/// All built-in error codes
/// @note These aren't actually used yet!
enum ErrorType
{
    SYNTAX_ERROR,
    UNDEFINED_ERROR,
}
typedef ErrorType;


/// A raw token or full Scheme value
struct Value
{
    int refCount;
    ValueType type;
    union
    {
        char paren;      /// PAREN_TOKEN

        char* symbol;    /// SYMBOL_VALUE
        bool boolVal;    /// BOOLEAN_VALUE
        int intVal;      /// INTEGER_VALUE
        float floatVal;  /// FLOAT_VALUE
        char* string;    /// STRING_VALUE

        struct           /// ERROR_VALUE
        {
            ErrorType error;
        };

        struct           /// FUNCTION_VALUE
        {
            struct Value* (*function) (struct Environment*, struct ParseTree*);
            bool keyword;
        };

        struct           /// LAMBDA_VALUE
        {
            struct Environment* environment;
            int numParams;
            char** params;
            struct ParseTree* code;
        };

        struct           /// LIST_VALUE
        {
            struct Value* head;
            struct Value* tail;
        };
    };
}
typedef Value;


/// Malloc and return a new Value with a refCount of 1
Value* value_create (ValueType type);

/// Create a BOOLEAN_VALUE
Value* value_create_bool (bool b);

/// Create a FLOAT_VALUE
Value* value_create_float (float x);

/// Create a C built-in function (like +, -, map, etc...)
Value* value_create_function (Value* (*func) (struct Environment*, struct ParseTree*));

/// Create a INTEGER_VALUE
Value* value_create_int (int x);

/// Create a C built-in keyword (like if, lambda, let, quote)
Value* value_create_keyword (Value* (*func) (struct Environment*, struct ParseTree*));

/// Create a Scheme lambda expression
Value* value_create_lambda (struct Environment* environment, int numParams, char** params, struct ParseTree* code);

/// Create an empty Scheme list
Value* value_create_list_empty ();

/// Create a Scheme cons box and reserve both head and tail (if not NULL)
Value* value_create_list (Value* head, Value* tail);

/// Increase a Value's refCount by 1
void value_reserve (Value* value);

/// Decrease the Value's refCount by 1, and free it if it reaches 0
void value_release (Value* value);

/// Display a Value followed by a space
void value_print (Value* value);

/// Display a Value Type and the Value itself followed by a space
void value_print_debug (Value* value);

/// Display a token Value in the form "type : value\n"
void token_print (Value* token);


#endif