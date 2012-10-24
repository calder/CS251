#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "Parser/Parser.h"
#include "Tokenizer/Tokenizer.h"
#include "Tokenizer/Tokens.h"
#include "Util/StringBuffer.h"


int main (int argc, char** argv)
{
    StringBuffer* buf = strbuf_create();
    Quack* cumulativeTokens = quack_create();
    Quack* parenStack = quack_create();


    while (true)
    {
        char c = getchar();
        
        if (c != EOF) { strbuf_append(buf, c); }
        else { strbuf_append(buf, '\n'); }
        if (c == '\n' || c == EOF)
        { 
            Quack* temptokens = tokenize(strbuf_data(buf));
            if (temptokens == NULL)
            {
                printf("Syntax Error\n");
                return 1;
            }
            strbuf_clear(buf);
            while (!quack_empty(temptokens))
            {
                quack_push_back(cumulativeTokens, quack_pop_front(temptokens));
                if (((Token*)quack_back(cumulativeTokens))->type == PAREN_TOKEN)
                {
                    if (((Token*)quack_back(cumulativeTokens))->parenData == '[' || ((Token*)quack_back(cumulativeTokens))->parenData == '(')
                    {
                        char *tmp = malloc(sizeof(int));
                        *tmp = (((Token*)quack_back(cumulativeTokens))->parenData);
                        quack_push_back(parenStack, tmp);
                    }
                    else
                    {
                        // Brackets and parenthese are close to their matches in the ascii alphabet, but are not close to their non matched pairs
                        if (quack_empty(parenStack)) {printf("Syntax Error\n");}
                        if (((int)((Token*)quack_back(cumulativeTokens))->parenData) - (*((int*)quack_back(parenStack)))  > 3)
                        {
                            printf("Syntax Error\n");
                            return 1;
                        }
                        free(quack_pop_back(parenStack));
                    }

                }
                if (quack_empty(parenStack))
                {
                    ParseTree* parsedTemp = parse(cumulativeTokens);
                    cumulativeTokens = quack_create();`

                    parsetree_print(parsedTemp);
                    printf("\n");
                    parsetree_free(parsedTemp);
                    while (!quack_empty(cumulativeTokens))
                    {
                        token_free(quack_pop_front(cumulativeTokens));
                    }
                }
            }
            quack_free(temptokens);
        }
        if (c == EOF) { break; }
    }

    if (!quack_empty(cumulativeTokens))
    {
        printf("Syntax Error\n");
        while (!quack_empty(cumulativeTokens))
        {   
            token_free(quack_pop_front(cumulativeTokens));
        }
    }
    quack_free(cumulativeTokens);
    while (!quack_empty(parenStack))
    {
        token_free(quack_pop_front(parenStack));
    }
    quack_free(parenStack);
    strbuf_free(buf);
    return 0;
}