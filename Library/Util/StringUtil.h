#ifndef STRINGUTIL_H
#define STRINGUTIL_H


/// Return a new string containing a portion of the original string
/// @note The calling function takes ownership of the returned
char* substring (char* original, int start, int end);


#endif