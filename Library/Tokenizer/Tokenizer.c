#include <stdlib.h>
#include <string.h>
#include "Tokenizer/States.h"
#include "Tokenizer/Tokenizer.h"
#include "Util/Quack.h"
#include "Util/Set.h"
#include "Util/StringUtil.h"


Quack* tokenize (char* input)
{
    Quack* tokens = quack_create();
    Set* nfa = set_create();

    int token_start = 0;
    for (int i = 0; true; ++i)
    {
        char c = input[i];
        if (c == 0) { break; }
        Set* next = advance_nfa(nfa, tokens, c);

        // Push a completed token
        if (set_empty(next))
        {
            char* token = substring(input, token_start, i-token_start);
            quack_push_back(tokens, token);
            set_free(next);
            set_clear(nfa);
            set_add(nfa, &start_state);
            token_start = i;
        }

        // Extend the current token
        else
        {
            set_free(nfa);
            nfa = next;
        }
    }

    set_free(nfa);
    return tokens;
}


Set* advance_nfa (Set* nfa, Quack* tokens, char c)
{
    return NULL; // Placeholder
}


void print_tokens (Quack* tokens)
{
    // Placeholder
}