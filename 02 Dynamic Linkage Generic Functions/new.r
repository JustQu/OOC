#ifndef CLASS_H
#define CLASS_H

#include "stdarg.h"

/*
**private header
*/

/*
Each of our objects starts with a pointer to its own type description, and through
this type description we can locate type-specific information for the object: .size is
the length that new() allocates for the object; .ctor points to the constructor called
by new() which receives the allocated area and the rest of the argument list passed
to new() originally; .dtor points to the destructor called by delete() which receives
the object to be destroyed; .clone points to a copy function which receives the
object to be copied; and .differ points to a function which compares its object to
something else.
*/
struct Class
{
    size_t  size;
    void    *(*ctor)(void *self, va_list *app);
    void    *(*dtor)(void *self);
    void    *(*clone)(const void *self);
    int     (*differ)(const void *self, const void *b);
};

#endif
