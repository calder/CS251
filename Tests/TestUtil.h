#ifndef TESTUTIL_H
#define TESTUTIL_H

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


/// Initialize the testing environment
/// @note TestUtil is an extremely lightweight unit testing framework.  Because
/// C has no concept of exceptions, it's very hard to handle failure gracefully
/// so we don't even try.  Instead, the second a test fails an assertion
/// TestUtil will actually crash your program as spectacularly as possible.  At
/// this point you go in with a debugger and figure out what the heck you did
/// wrong.  You monster.
void start_testing ();

/// Clean up the testing environment and print result summary
void finish_testing ();

/// Mark the beginning of a new test
/// @note start() may only be called when there is no test currently running.
/// @note The calling function maintains ownership of the string <testName>.
void start_test (const char* testName);


#endif