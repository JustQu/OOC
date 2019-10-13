#ifndef NAME_R
# define NAME_R

struct Name             /* base structure */
{
    const void  *type;  /* for  dynamic linkage */
    const char  *name;  /* may be malloc-ed */
    int         token;
};

#endif
