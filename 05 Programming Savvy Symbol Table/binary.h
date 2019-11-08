#ifndef BINARY_H
# define BINARY_H

#include <stddef.h>

void	*binary(const void *key, void *base, size_t *nelp,
		size_t width, int (*cmp)(const void *key, const void *elt));

#endif
