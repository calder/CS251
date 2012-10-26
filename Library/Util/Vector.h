#ifndef VECTOR_H
#define VECTOR_H


/// An expanding array of elements
struct
{
    void** array;
    int size;
    int capacity;
}
typedef Vector;


/// Malloc and return an empty Vector
Vector* vector_create ();

/// Free the Vector itself, leaving its contents untouched
void vector_free (Vector* vector);

/// Display the entire vector
void vector_print (Vector* vector);

/// Return true iff the Vector has 0 items in it
int vector_empty (Vector* vector);

/// Return the number of items in the vector
int vector_size (Vector* vector);

/// Return the item stored at <index>
void* vector_get (Vector* vector, int index);

/// Change the item stored at <index>
void vector_set (Vector* vector, int index, void* item);

/// Add an item to the end of the vector
void vector_append (Vector* vector, void* item);


#endif