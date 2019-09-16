#include "new.h"
#include "Class.h"

void    *new(const void *_class, ...)
{
    const struct Class  *class = _class;
    void                *p = calloc(1, class->size);

    assert(p);
    *(const struct Class **)p = class; /*We force a
conversion of p which treats the beginning of the object as a pointer to a struct
Class and set the argument class as the value of this pointer.*/

    if (class->ctor)
    {
        va_list ap;

        va_start(ap, _class);
        p = class->ctor(p, &ap);
        va_end(ap);
    }
    return p;
}

void    delete(void    *self)
{
    const struct Class **cp = self;

    if (self &&  *cp && (*cp)->dtor)
        self = (*cp)->dtor(self);
    free(self);
}

int     differ(const void *self, const void *b)
{
    const struct Class *const *cp = self;
    
    assert(self  && *cp && (*cp)->differ);
    return (*cp)->differ(self, b);
}

size_t  sizeOf(const void *self)
{
    const struct Class *const *cp = self;

    assert(self && *cp);
    return (*cp)->size;
}
