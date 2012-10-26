#include <stdlib.h>
#include "Interpreter/Binding.h"
#include "Util/StringUtil.h"


Binding* binding_create (const char* symbol, Value* value)
{
    Binding* binding = malloc(sizeof(Binding));
    binding->symbol = dupstring(symbol);
    binding->value = value;
    value_reserve(value);
    return binding;
}


void binding_free (Binding* binding)
{
    value_release(binding->value);
    free(binding->symbol);
    free(binding);
}