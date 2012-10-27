#include <assert.h>
#include <stdlib.h>
#include "Interpreter/Interpreter.h"
#include "Tokenizer/Tokens.h"
#include "Util/StringUtil.h"


Value* evaluate_primitive (ParseTree* parseTree, Environment* environment);


Value* evaluate (ParseTree* parseTree, Environment* environment)
{
    if (parseTree->token != NULL) { return evaluate_primitive(parseTree,environment); }

syntax_error:

    parsetree_free(parseTree);
    return NULL;
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

    parsetree_free(parseTree);
    return value;
}