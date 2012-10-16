#include <stdio.h>
#include <string.h>
#include "Util/Set.h"
#include "Util/StringBuffer.h"
#include "Tokenizer/States.h"
#include "Tokenizer/Tokenizer.h"


int main (int argc, char** argv)
{
    Quack* tokens = quack_create();
    Set* nfa = set_create();
    StringBuffer* token = strbuf_create();

    while (true)
    {
        char c = getchar();
        if (c == EOF) { break; }
        Set* next = advance_nfa(nfa, tokens, c);

        // Push a completed token
        if (set_empty(next))
        {
            quack_push_back(tokens, token);
            set_free(next);
            set_clear(nfa);
            set_add(nfa, &start_state);
            strbuf_clear(token);
        }

        // Extend the current token
        else
        {
            strbuf_append(token, c);
            set_free(nfa);
            nfa = next;
        }
    }

    set_free(nfa);
    quack_free(tokens);

    return 0;
}