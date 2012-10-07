#include <stdio.h>

#include "TestUtil.h"
#include "TokenizerTests.h"


int main (int argc, char** argv)
{
    startTesting();
    testTokenizer();
    finishTesting();
    return 0;
}