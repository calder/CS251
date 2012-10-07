#ifndef TESTUTIL_H
#define TESTUTIL_H

#include <stdbool.h>


/// Initialize testing environment
void startTesting ();

/// Print a summary of all tests run
void finishTesting ();

/// Mark the beginning of a new test
/// @note start() may only be called when there is no test currently running.
/// @note The calling function maintains ownership of <testName>.{{}}
void start (const char* testName);

/// Mark the successfull end of a test
/// @note finish() may only be called when there is a test already running.
void finish ();

/// Exit the current test and mark it as failed
void fail ();

/// Fail the current test iff <x> is false
void failIfFalse (bool x);

/// Fail the current test iff <x> is true
void failIfTrue (bool x);

/// Fail the current test iff two pointers are not equal
void failIfDifferent (const void* x, const void* y);

/// Fail the current test iff two integers are not equal
void failIfUnequal (int x, int y);


#endif