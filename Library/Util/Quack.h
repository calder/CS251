#ifndef QUACK_H
#define QUACK_H

#include <stdbool.h>


/// A double ended queue-stack hybrid implemented with a rotating array
struct
{
    void** array;
    int start;
    int size;
    int capacity;
}
typedef Quack;


/// Malloc, initialize and return an empty Quack
Quack* quack_create ();

/// Free the Quack itself, leaving its contents untouched
void quack_free (Quack* quack);

/// Display the entire Quack for debugging purposes
void quack_print (Quack* quack);

/// Return true iff the Quack contains 0 items
bool quack_empty (Quack* quack);

/// Return the number of items in the Quack
int quack_size (Quack* quack);

/// Add a new item to the front of the Quack
void quack_push_front (Quack* quack, void* item);

/// Add a new item to the back of the Quack
void quack_push_back (Quack* quack, void* item);

/// Remove and return the item at the front of the Quack
void* quack_pop_front (Quack* quack);

/// Remove and return the item at the back of the Quack
void* quack_pop_back (Quack* quack);

/// Return (without removing) the item at the front of the Quack
void* quack_front (Quack* quack);

/// Return (without removing) the item at the back of the Quack
void* quack_back (Quack* quack);


#endif