#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Parser/Parser.h"
#include "Tokenizer/Tokenizer.h"
#include "Util/StringBuffer.h"


int main(int argc, char** argv)
{
	StringBuffer* buf = strbuf_create();

	char c;
    Quack* cumulativeTokens = quack_create();
    Quack* parenStack = quack_create();
    while (c != EOF)
    {
        
        
        c = getchar();
        strbuf_append(buf, c);
        if (c == '\n' || c == EOF)
        { 
            strbuf_append(buf, '\n');
            Quack* temptokens = tokenize(strbuf_data(buf));
            while (!quack_empty(temptokens))
            {
                quack_push_front(cumulativeTokens, quack_pop_back(temptokens));
                if (((Token*)quack_front(cumulativeTokens))->type == PAREN_TOKEN)
                {
                    if(((Token*)quack_front(cumulativeTokens))->parenData == '[' || ((Token*)quack_front(cumulativeTokens))->parenData == '(')
                    {
                        quack_push_front(parenStack, &(((Token*)quack_front(cumulativeTokens))->parenData));
                    }
                    else
                    {
                        // Brackets and parenthese are close to their matches in the ascii alphabet, but are not close to their non matched pairs
                        if (((int)(quack_pop_front(parenStack))) - ((int)((Token*)quack_front(cumulativeTokens))->parenData)  > 3)
                        {
                            printf("Syntax Error\n");
                            return 1;
                        }
                    }

                    if (quack_empty(parenStack))
                    {
                        ParseTree* parsedTemp = parse(cumulativeTokens);
                        while (!quack_empty(cumulativeTokens))
                        {
                            token_free(quack_pop_front(cumulativeTokens));
                        }
                        parsetree_print(parsedTemp);
                        parsetree_free(parsedTemp);
                    }
                }
            }
            quack_free(temptokens);
        }
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