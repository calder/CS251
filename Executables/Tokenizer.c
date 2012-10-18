#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Tokenizer/Tokenizer.h"
#include "Util/StringBuffer.h"


int main (int argc, char** argv)
{
    StringBuffer* buf = strbuf_create();

    /*
    while (true)
    {
        char c = getchar();
        if (c == EOF) { break; }
        strbuf_append(buf, c);
    }
    */

    // strbuf_append(buf,'\n');
    // Quack* tokens = tokenize(strbuf_data(buf));
    Quack* tokens = tokenize("( ()asdf)]123) 509.5\n");
    print_tokens(tokens);

    // quack_free_with_contents(tokens);
    quack_free(tokens);
    strbuf_free(buf);
    return 0;
}