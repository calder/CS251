#include <stdio.h>

#include "QuackTests.h"
#include "TestUtil.h"
#include "TokenizerTests.h"


int main (int argc, char** argv)
{
    startTesting();

    testQuack();
    testTokenizer();

    finishTesting();
    return 0;
}