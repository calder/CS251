#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include "Tokenizer/Value.h"
#include "Util/Vector.h"


/// A reference counted list of variable bindings
struct Environment
{
    int refCount;
    struct Environment* parent;
    Vector* bindings;
}
typedef Environment;


/// Malloc and return a new Environment with a refCount of 1
/// @note The parent environment will be reserved.
/// @note The root environment should pass NULL as it's parent; create() will
/// not attempt to reserve NULL.
Environment* environment_create (Environment* parent);

/// Convenience function to initialize an environment with all built-ins defined
Environment* environment_create_default ();

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