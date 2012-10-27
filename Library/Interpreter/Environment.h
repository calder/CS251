#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include "Interpreter/Value.h"
#include "Util/Vector.h"


/// A reference counted list of variable bindings
struct __Environment
{
    int refCount;
    struct __Environment* parent;
    Vector* bindings;
}
typedef Environment;


/// Initialize a new default Environment containing all built-in functions
Environment* environment_create_default ();

/// Malloc and return a new Environment with a refCount of 1
/// @note The parent environment will be reserved.
/// @note The root environment should pass NULL as it's parent; create() will
/// not attempt to reserve NULL.
Environment* environment_create (Environment* parent);

/// Increase an environment's refCount by 1
void environment_reserve (Environment* environment);

/// Decrease the Value's refCount by 1, and free it if it reaches 0
void environment_release (Environment* environment);

/// Display an Environment
void environment_print (Environment* environment);

/// Return the Value bound to a symbol, or NULL if unbound
Value* environment_get (Environment* environment, const char* symbol);

/// Set the Value bound to a symbol and reserve the Value
void environment_set (Environment* environment, const char* symbol, Value* value);


#endif