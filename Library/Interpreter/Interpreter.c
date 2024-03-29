#include <assert.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "Interpreter/Functions.h"
#include "Interpreter/Interpreter.h"
#include "Tokenizer/Value.h"
#include "Parser/Parser.h"
#include "Util/StringBuffer.h"
#include "Util/StringUtil.h"


Value* evaluate_function (ParseTree* parseTree, Environment* environment);
Value* evaluate_primitive (ParseTree* parseTree, Environment* environment);

Value* evaluate_lambda (Value* lambda, ParseTree* args, Environment* environment);


Quack* interpret (const char* input)
{
    // Parse input into expression trees
    Environment* environment = environment_create_default();
    Quack* values = quack_create();
    Quack* expressions = parse(input);
    if (expressions == NULL) { environment_release(environment); quack_free(values); return NULL; }

    // Evaluate each expression tree
    while (!quack_empty(expressions))
    {
        ParseTree* parseTree = quack_pop_front(expressions);
        Value* value = evaluate(parseTree, environment);
        if (value == NULL) { goto error; }
        parsetree_release(parseTree);
        quack_push_back(values, value);
    }

    // Clean up and return evaluated expressions
    environment_release(environment);
    quack_free(expressions);
    return values;

error:
    
    while (!quack_empty(expressions)) { parsetree_release(quack_pop_front(expressions)); }
    environment_release(environment);
    quack_free(expressions);
    return NULL;
}


Value* evaluate (ParseTree* parseTree, Environment* environment)
{
    if (parseTree->token != NULL) { return evaluate_primitive(parseTree,environment); }
    else                          { return evaluate_function(parseTree,environment); }
}


Value* evaluate_nokeyword (ParseTree* parseTree, Environment* environment)
{
    Value* value = evaluate(parseTree, environment);
    if (value != NULL && value->type == FUNCTION_VALUE && value->keyword)
    {
        value_release(value);
        return NULL;
    }
    return value;
}


Value* evaluate_list (ParseTree* parseTree)
{
    // Primitive case (leaf)
    if (parseTree->token != NULL) { return evaluate_primitive(parseTree,NULL); }

    // List construction (subtree)
    Value* list = value_create_list_empty();
    for (int i = parseTree->numChildren - 1; i >= 0; --i)
    {
        Value* item = evaluate_list(parseTree->children[i]);
        if (item == NULL) { value_release(list); return NULL; }
        Value* head = value_create(LIST_VALUE);
        head->head = item;
        head->tail = list;
        list = head;
    }
    return list;
}


Value* evaluate_bodies (ParseTree* parseTree, Environment* environment)
{
    // Evaluate each body expression
    Value* value = NULL;
    for (int i = 2; i < parseTree->numChildren; ++i)
    {
        if (value != NULL) { value_release(value); }
        value = evaluate(parseTree->children[i], environment);
        if (value == NULL) { break; }
    }

    // And return the last
    environment_release(environment);
    return value;
}


Value* evaluate_function (ParseTree* parseTree, Environment* environment)
{
    // Check number of arguments
    if (parseTree->numChildren < 1) { return NULL; }
    // Evaluate the first argument (which is hopefully a function)
    Value* f = evaluate(parseTree->children[0], environment);
    if (f == NULL) { return NULL; }

    // Apply function and return result
    Value* result = NULL;
    if (f->type == FUNCTION_VALUE) { result = f->function(environment, parseTree); }
    if (f->type == LAMBDA_VALUE)   { result = evaluate_lambda(f, parseTree, environment); }
    value_release(f);
    return result;  
}


Value* evaluate_primitive (ParseTree* parseTree, Environment* environment)
{
    Value* token = parseTree->token;
    Value* value;

    switch (token->type)
    {
    case BOOLEAN_VALUE:
        value = value_create(BOOLEAN_VALUE);
        value->boolVal = token->boolVal;
        break;
    case FLOAT_VALUE:
        value = value_create(FLOAT_VALUE);
        value->floatVal = token->floatVal;
        break;
    case INTEGER_VALUE:
        value = value_create(INTEGER_VALUE);
        value->intVal = token->intVal;
        break;
    case STRING_VALUE:
        value = value_create(STRING_VALUE);
        value->string = dupstring(token->string);
        break;
    case SYMBOL_VALUE:
        if (environment == NULL)
        {
            value = value_create(SYMBOL_VALUE);
            value->symbol = dupstring(token->symbol);
        }
        else
        {
            value = environment_get(environment, token->symbol);
            if (value != NULL) { value_reserve(value); }
        }
        break;
    default:
        assert(false);
    }

    return value;
}


Value* evaluate_lambda (Value* lambda, ParseTree* args, Environment* environment)
{
    if ((args->numChildren - 1) != lambda->numParams) { return NULL; }
    Environment* env = environment_create(lambda->environment);

    for (int i = 0; i < lambda->numParams; ++i)
    {
        Value* arg = evaluate(args->children[i+1], environment);
        if (arg == NULL) { environment_release(env); return NULL; }
        environment_set(env, lambda->params[i], arg);
        value_release(arg);
    }
    return evaluate_bodies(lambda->code, env);
}


bool load_file (Environment* environment, const char* filename)
{
    // Get file handle
    int f = open(filename, O_RDONLY);
    if (f == -1) { return false; }

    // Get file size
    struct stat statbuf;
    if (fstat(f, &statbuf) == -1) { return false; }

    // Memory map file
    char* file = mmap(NULL, statbuf.st_size, PROT_READ, MAP_SHARED, f, 0);
    close(f);
    if (file == MAP_FAILED) { return false; }

    // Parse file into parse tree
    StringBuffer* fileContents = strbuf_create();
    for (int i = 0; i<statbuf.st_size; ++i)
    {
        strbuf_append(fileContents, file[i]);
    }
    Quack* expressions = parse(strbuf_data(fileContents));
    if (expressions == NULL) { goto error; }

    // Interpret parse tree
    while (!quack_empty(expressions))
    {
        ParseTree* expression = quack_pop_front(expressions);
        Value* value = evaluate(expression, environment);
        parsetree_release(expression);
        if (value == NULL) { goto error; }
        if (value->type != NULL_VALUE) { value_print(value); printf("\n"); }
        value_release(value);
    }

    munmap(file, statbuf.st_size);
    strbuf_free(fileContents);
    quack_free(expressions);
    return true;

error:
    
    munmap(file, statbuf.st_size);
    strbuf_free(fileContents);
    if (expressions != NULL) { quack_free(expressions); }
    return false;
}