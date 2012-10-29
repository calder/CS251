#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "Interpreter/Value.h"


Value* function_if (Closure* closure, ParseTree* args);
Value* function_let (Closure* closure, ParseTree* args);
Value* function_lambda (Closure* closure, ParseTree* args);
Value* function_quote (Closure* closure, ParseTree* args);


#endif