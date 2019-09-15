#ifndef NEW_H
#define NEW_H

/* memory management*/

/*
new() accepts a descriptor like Set and possibly more
arguments for initialization and returns a pointer to a
new data item with a representation conforming to
the descriptor
*/
void	*new(const void *type, ...);

/*
delete() accepts a pointer originally produced by new() and recycles
the associated resources.
*/
void	delete(void *item);

#endif
