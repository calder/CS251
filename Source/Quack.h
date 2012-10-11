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


/// Malloc and return a new Quack
Quack* createQuack ();

/// Free the Quack itself, leaving its contents untouched
void freeQuack (Quack* quack);

/// Free the Quack and everything in it
void freeQuackAndContents (Quack* quack);

/// Display the entire Quack for debugging purposes
void print (Quack* quack);

/// Return true iff the Quack contains no items
bool empty (Quack* quack);

/// Add a new item to the front of the Quack
void pushFront (Quack* quack, void* item);

/// Add a new item to the back of the Quack
void pushBack (Quack* quack, void* item);

/// Remove and return the item at the front of the Quack
void* popFront (Quack* quack);

/// Remove and return the item at the back of the Quack
void* popBack (Quack* quack);

/// Return (without removing) the item at the front of the Quack
void* front (Quack* quack);

/// Return (without removing) the item at the back of the Quack
void* back (Quack* quack);

/// Remove and free the item at the front of the Quack
void freeFront (Quack* quack);

/// Remove and free the item at the back of the Quack
void freeBack (Quack* quack);


#endif