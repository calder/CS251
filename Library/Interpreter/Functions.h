#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "Interpreter/Environment.h"
#include "Parser/ParseTree.h"

Value* function_append (Environment* environment, ParseTree* args);
Value* function_begin (Environment* environment, ParseTree* args);   // Not implemented
Value* function_car (Environment* environment, ParseTree* args);
Value* function_cdr (Environment* environment, ParseTree* args);
Value* function_cons (Environment* environment, ParseTree* args);
Value* function_cond (Environment* environment, ParseTree* args);    // Not implemented
Value* function_define (Environment* environment, ParseTree* args);
Value* function_display (Environment* environment, ParseTree* args);
Value* function_divide (Environment*  environment, ParseTree* args);
Value* function_greaterthen (Environment* environment, ParseTree* args);
Value* function_greatertheneqto (Environment* environment, ParseTree* args);
Value* function_if (Environment* environment, ParseTree* args);
Value* function_lambda (Environment* environment, ParseTree* args);
Value* function_lessthen (Environment* environment, ParseTree* args);
Value* function_lesstheneqto (Environment* environment, ParseTree* args);
Value* function_let (Environment* environment, ParseTree* args);
Value* function_letrec (Environment* environment, ParseTree* args);
Value* function_letstar (Environment* environment, ParseTree* args); // Not fully implemented
Value* function_list (Environment* environment, ParseTree* args);
Value* function_load (Environment* environment, ParseTree* args);
Value* function_minus (Environment*  environment, ParseTree* args);
Value* function_numequals (Environment*  environment, ParseTree* args);
Value* function_null (Environment*  environment, ParseTree* args);
Value* function_plus (Environment*  environment, ParseTree* args);
Value* function_quote (Environment* environment, ParseTree* args);
Value* function_setbang (Environment* environment, ParseTree* args);
Value* function_times (Environment*  environment, ParseTree* args);


#endif