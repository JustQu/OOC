#ifndef SET_H
#define SET_H

/*
Set will have to somehow represent the fact, that we are working with sets
*/
extern const void *Set;

/*
add() takes an element, adds it to a set, and returns
whatever was added or 
already present in the set
*/
void 	*add(void *set, const void *element);

/*
find() looks for an element in a set and returns
whatever is present in the set or a null pointer
*/
void 	*find(const void *set, const void *element);

/*
drop() locates an element, removes it from
a set, and returns whatever was removed
*/
void 	*drop(void *set, const void *element);

/*
contains() converts the result of find()
into a truth value.

*/
int		contains(const void *set, const void *element);

#endif
