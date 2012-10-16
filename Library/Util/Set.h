#ifndef SET_H
#define SET_H

#include <stdbool.h>


/// A collection of unique elements stored in a hash table
struct
{
    void** array;
    int size;
    int capacity;
}
typedef Set;


/// Malloc and return a new Set
Set* set_create ();

/// Free the Set itself, leaving its contents untouched
void set_free (Set* set);

/// Remove everything from the Set
void set_clear (Set* set);

/// Display the entire Set for debugging purposes
void set_print (Set* set);

/// Return the number of items in the Set
int set_size (Set* set);

/// Return true iff the Set's size is 0
bool set_empty (Set* set);

/// Insert a new item into the Set iff it isn't already in the set
void set_add (Set* set, void* item);

/// Remove an item from the Set
void set_remove (Set* set, void* item);

/// Return true iff an item is in the Set
bool set_contains (Set* set, void* item);


#endif