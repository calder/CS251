#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "Util/StringUtil.h"


char* substring (const char* original, int start, int end)
{
    assert((start >= 0) && (start < end) && (end <= strlen(original)));
    char* sub = malloc(sizeof(char) * (end - start + 1));
    memcpy(sub, &original[start], end - start);
    sub[end-start] = 0;
    return sub;
}