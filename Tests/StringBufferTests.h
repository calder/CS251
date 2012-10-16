#ifndef STRINGBUFFERTESTS_H
#define STRINGBUFFERTESTS_H

#include <string.h>
#include "Util/StringBuffer.h"
#include "TestUtil.h"


void test_strbuf_append ()
{
    start_test("StringBuffer - Append");
    StringBuffer* buf = strbuf_create();

    for (int c = 0; c < 128; ++c) { strbuf_append(buf, c); }
    const char* string = strbuf_data(buf);
    for (int c = 0; c < 128; ++c) { assert(string[c] == c); }

    strbuf_free(buf);
}


void test_strbuf_append_string ()
{
    start_test("StringBuffer - Append String");
    StringBuffer* buf = strbuf_create();
    const char* str1 = "nana ";
    const char* str2 = "batman";
    const char* str3 = "nana nana nana nana batman";
    int length = strlen(str3);

    for (int i = 0; i < 4; ++i) { strbuf_append_string(buf, str1); }
    strbuf_append_string(buf, str2);
    const char* string = strbuf_data(buf);
    for (int i = 0; i < length; ++i) { assert(string[i] == str3[i]); }

    strbuf_free(buf);
}


void test_strbuf_clear ()
{
    start_test("StringBuffer - Clear");
    StringBuffer* buf = strbuf_create();

    for (int c = 0; c < 64; ++c) { strbuf_append(buf, c); }
    strbuf_clear(buf);
    for (int c = 0; c < 64; ++c) { strbuf_append(buf, c+64); }
    const char* string = strbuf_data(buf);
    for (int c = 0; c < 64; ++c) { assert(string[c] == c + 64); }

    strbuf_free(buf);
}


void test_strbuf ()
{
    test_strbuf_append();
    test_strbuf_append_string();
    test_strbuf_clear();
}


#endif