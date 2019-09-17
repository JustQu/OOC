#ifndef NEW_H
#define NEW_H

#include "stddef.h"

void    *new(const void *_class, ...);
void    delete(void *self);
void    *clone(const void *self);
int     differ(const void *self, const void *b);
size_t  sizeOf(const void *self);

#endif
