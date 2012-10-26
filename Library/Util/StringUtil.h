#ifndef STRINGUTIL_H
#define STRINGUTIL_H


/// Return a new string that is an exact copy of the original
/// @note The calling function takes ownership of the returned string.
char* dupstring (const char* original);


/// Return a new string containing a portion of the original string
/// @note The calling function takes ownership of the returned string.
char* substring (const char* original, int start, int end);


#endif