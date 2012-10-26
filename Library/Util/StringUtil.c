#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "Util/StringUtil.h"


char* dupstring (const char* original)
{
    int length = strlen(original);
    char* dup = malloc(sizeof(char) * (length + 1));
    strcpy(dup, original);
    dup[length] = 0;
    return dup;
}


char* substring (const char* original, int start, int end)
{
    assert((start >= 0) && (start < end) && (end <= strlen(original)));
    char* sub = malloc(sizeof(char) * (end - start + 1));
    memcpy(sub, &original[start], end - start);
    sub[end-start] = 0;
    return sub;
}