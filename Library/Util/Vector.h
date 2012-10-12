struct
{
    void** array;
    int size;
    int capacity;
}
typedef Vector;


/// Malloc, initialize and return an empty Vector
Vector* vector_create ();

/// Free the Vector itself, leaving its contents untouched
void vector_free (Vector* vector);

/// Free the Vector and everything in it
void vector_free_with_contents (Vector* vector);

/// Display the entire vector
void vector_print (Vector* vector);

/// Return the number of items in the vector
int vector_size (Vector* vector);

/// Return the item stored at <index>
void* vector_get (Vector* vector, int index);

/// Change the item stored at <index>
void vector_set (Vector* vector, int index, void* item);

/// Put <item> at <index> after shifting things down to make room
void vector_insert (Vector* vector, int index, void* item);

/// Remove (but don't free) the item at <index>
void vector_remove (Vector* vector, int index);

/// Remove and free the item the item at <index>
void vector_remove_and_free (Vector* vector, int index);