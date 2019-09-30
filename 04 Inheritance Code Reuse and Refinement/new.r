#ifndef NEW_R
# define NEW_R

#include <stdarg.h>
#include <stddef.h>

struct Class
{
	size_t	size;
	void    *(*ctor)(void *self, va_list *app);
	void	*(*dtor)(void *self);
	void	(*draw)(const void *self);
};

#endif
