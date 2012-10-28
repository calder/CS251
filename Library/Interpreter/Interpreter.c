#include <assert.h>
#include <stdlib.h>
#include "Interpreter/Interpreter.h"
#include "Interpreter/Value.h"
#include "Parser/Parser.h"
#include "Tokenizer/Tokens.h"
#include "Util/StringUtil.h"


Value* evaluate_function (ParseTree* parseTree, Environment* environment);
Value* evaluate_primitive (ParseTree* parseTree, Environment* environment);


Quack* interpret (const char* input)
{
    Environment* environment = environment_create_default();
    Quack* values = quack_create();
    Quack* expressions = parse(input);

    while (!quack_empty(expressions))
    {
        ParseTree* parseTree = quack_pop_front(expressions);
        Value* value = evaluate(parseTree, environment);
        parsetree_release(parseTree);
        quack_push_back(values, value);
    }

    quack_free(expressions);
    return values;
}


Value* evaluate (ParseTree* parseTree, Environment* environment)
{
    Value* value;
    if (parseTree->token != NULL) { value = evaluate_primitive(parseTree, environment); }
    else                          { value = evaluate_function(parseTree, environment); }

    if (value->type == EXPRESSION_VALUE)
    { 
        Value* finalValue = evaluate(value->exprVal, environment);
        value_release(value);
        value = finalValue;
    }
    
    return value;
}


Value* evaluate_function (ParseTree* parseTree, Environment* environment)
{
    if (parseTree->numChildren < 1) { return NULL; }
    Value* f = evaluate(parseTree->children[0], environment);
    if (f->type != FUNCTION_VALUE) { value_release(f); return NULL; }

    Value* result = f->funcVal.function(&f->funcVal, parseTree);
    value_release(f);
    return result;
}


Value* evaluate_primitive (ParseTree* parseTree, Environment* environment)
{
    Token* token = parseTree->token;
    Value* value;

    switch (token->type)
    {
    case BOOLEAN_TOKEN:
        value = value_create(BOOLEAN_VALUE);
        value->boolVal = token->boolVal;
        break;
    case FLOAT_TOKEN:
        value = value_create(FLOAT_VALUE);
        value->floatVal = token->floatVal;
        break;
    case INTEGER_TOKEN:
        value = value_create(INTEGER_VALUE);
        value->intVal = token->intVal;
        break;
    case STRING_TOKEN:
        value = value_create(STRING_VALUE);
        value->stringVal = dupstring(token->stringVal);
        break;
    case SYMBOL_TOKEN:
        value = environment_get(environment, token->symbolVal);
        break;
    default:
        assert(false);
    }

    return value;
}