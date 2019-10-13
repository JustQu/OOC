#ifndef NAME_H
# define NAME_H

extern void *symbol;	/* last Name found by screen() */

void    install(const void *symbol);
int     screen(const char *name);

#endif
