#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "TestUtil.h"


clock_t       startTime;
int           testCount;

const char*   currentTestName = NULL;
clock_t       currentTestStart;

void finish_test ();


void start_testing ()
{
    startTime = clock();
    testCount = 0;
    printf("+----------------------------------------------------------+\n");
}


void finish_testing ()
{
    finish_test();
    double time = ((double)(clock() - startTime)) / CLOCKS_PER_SEC;
    char result[20];
    sprintf(result, "%d TESTS PASSED", testCount);
    printf("|                                                          |\n");
    printf("| %-20s                           %fs |\n", result, time);
    printf("+----------------------------------------------------------+\n");
}


void start_test (const char* testName)
{
    finish_test();
    currentTestName = testName;
    currentTestStart = clock();
}


void finish_test ()
{
    if (currentTestName == NULL) { return; }
    ++testCount;
    const char* name = currentTestName;
    double time = ((double)(clock() - currentTestStart)) / CLOCKS_PER_SEC;
    printf("| %-43s    %fs |\n", name, time);
    currentTestName = NULL;
}