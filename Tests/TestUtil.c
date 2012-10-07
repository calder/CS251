#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "TestUtil.h"


bool          testingStarted = false;
clock_t       startTime;
unsigned int  testsPassed;
unsigned int  testsFailed;

const char*   currentTestName = NULL;
clock_t       currentTestStart;


void startTesting ()
{
    assert(!testingStarted);
    startTime = clock();
    testsPassed = 0;
    testsFailed = 0;
    testingStarted = true;
    printf("+----------------------------------------------------------+\n");
}


void finishTesting ()
{
    assert(testingStarted);
    double time = ((double)(clock() - startTime)) / CLOCKS_PER_SEC;
    char passed[20];
    sprintf(passed, "%d/%d PASSED", testsPassed, testsPassed + testsFailed);
    printf("|                                                          |\n");
    printf("| TOTAL                    %20s  %fs |\n", passed, time);
    printf("+----------------------------------------------------------+\n");
    testingStarted = false;
}


void start (const char* testName)
{
    assert(currentTestName == NULL);
    currentTestName = testName;
    currentTestStart = clock();
}


void finishTest (bool passed)
{
    assert(currentTestName != NULL);
    passed ? ++testsPassed : ++testsFailed;

    const char* name = currentTestName;
    const char* result = passed ? "PASSED" : "FAILED";
    double time = ((double)(clock() - currentTestStart)) / CLOCKS_PER_SEC;

    printf("| %-37s  %s  %fs |\n", name, result, time);
    currentTestName = NULL;
}


void finish ()
{
    finishTest(true);
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