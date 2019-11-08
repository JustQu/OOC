#ifndef VALUE_R
# define VALUE_R

#include <stdarg.h>

struct Type
{
	void	*(*new)(va_list ap);
	double	(*exec)(const void *tree);
	void	(*delete)(void *tree);
};

#endif
