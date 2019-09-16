#include "stdlib.h"

struct type
{
    size_t  size;               /* size of an object */
    void    (*dtor)(void *);    /* destructor */
};

struct string
{
    char        *text;      /* dynamic string */
    const void  *destroy;   /* locate destructor */
};

struct Set
{
    /* information */
    const void  *destroy;   /* locate destructor */
};


