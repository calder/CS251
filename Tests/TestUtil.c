#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "TestUtil.h"


clock_t       startTime;
int           testsPassed;
int           testsFailed;

const char*   currentTestName = NULL;
clock_t       currentTestStart;

void finishTest (bool passed);


void startTesting ()
{
    startTime = clock();
    testsPassed = 0;
    testsFailed = 0;
    printf("+----------------------------------------------------------+\n");
}


void finishTesting ()
{
    finishTest(true);
    double time = ((double)(clock() - startTime)) / CLOCKS_PER_SEC;
    char result[20];
    sprintf(result, "%d FAILED", testsFailed);
    if (testsFailed == 0) { sprintf(result, "ALL PASSED"); }
    printf("|                                                          |\n");
    printf("| TOTAL                    %20s  %fs |\n", result, time);
    printf("+----------------------------------------------------------+\n");
}


void startTest (const char* testName)
{
    finishTest(true);
    currentTestName = testName;
    currentTestStart = clock();
}


void finishTest (bool passed)
{
    if (currentTestName == NULL) { return; }
    passed ? ++testsPassed : ++testsFailed;

    const char* name = currentTestName;
    const char* result = passed ? "PASSED" : "FAILED";
    double time = ((double)(clock() - currentTestStart)) / CLOCKS_PER_SEC;

    printf("| %-37s  %s  %fs |\n", name, result, time);
    currentTestName = NULL;
}


void fail ()
{
    finishTest(false);
}


void failIfTrue (bool x)
{
    if (x) { fail(); }
}


void failIfFalse (bool x)
{
    if (!x) { fail(); }
}


void failIfDifferent (const void* x, const void* y)
{
    if (x != y) { fail(); }
}