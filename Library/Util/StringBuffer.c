#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Util/StringBuffer.h"
#include "Util/StringUtil.h"


StringBuffer* strbuf_create ()
{
    StringBuffer* buf = (StringBuffer*) malloc(sizeof(StringBuffer*));
    buf->length = 0;
    buf->capacity = 4;
    buf->data = (char*) malloc(4 * sizeof(char*));
    buf->data[0] = 0;
    return buf;
}


void strbuf_clear (StringBuffer* buf)
{
    buf->data[0] = 0;
    buf->length = 0;
}


void strbuf_free (StringBuffer* buf)
{
    free(buf->data);
    free(buf);
}


void strbuf_print (StringBuffer* buf)
{
    printf("\"%s\"", buf->data);
}


void strbuf_append (StringBuffer* buf, char c)
{
    if (buf->length + 1 >= buf->capacity)
    {
        char* newData = (char*) malloc(2 * buf->capacity * sizeof(char));
        memcpy(newData, buf->data, buf->capacity * sizeof(char));
        free(buf->data);
        buf->data = newData;
        buf->capacity *= 2;
    }
    buf->data[buf->length] = c;
    buf->data[buf->length+1] = 0;
    buf->length += 1;
}


void strbuf_append_string (StringBuffer* buf, const char* string)
{
    int l = strlen(string);
    if (buf->length + l >= buf->capacity)
    {
        int newCapacity = buf->capacity;
        while (buf->length + l >= newCapacity) { newCapacity *= 2; }
        char* newData = (char*) malloc(newCapacity * sizeof(char));
        memcpy(newData, buf->data, buf->capacity * sizeof(char));
        free(buf->data);
        buf->data = newData;
        buf->capacity = newCapacity;
    }
    memcpy(&buf->data[buf->length], string, l+1);
    buf->length += l;
}


const char* strbuf_data (StringBuffer* buf)
{
    return buf->data;
}