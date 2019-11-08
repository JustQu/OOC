#include "Name.h"
#include "Name.r"

#include "parse.h"
#include "binary.h"

#include <string.h>
#include <stdlib.h>
#include <assert.h>

#ifndef NAMES
# define NAMES 4 /* initial allotment of tables entries;
					each time we run out we double the size pf the table */
#endif

static int cmp(const void *_key, const void *_elt)
{
	const char *const *key = _key;
	const struct Name *const *elt = _elt;

	return strcmp(*key, (*elt)->name);
}

static struct Name **search(const char **name)
{
	static const struct Name **names; /* dynamic table */
	static size_t used, max;

	if (used >= max)
	{
		names = names
			? realloc(names, (max *= 2) * sizeof *names)
			: malloc((max = NAMES) * sizeof *names);
		assert(names);
	}
	return binary(name, names, &used, sizeof *names, cmp);
}

int screen(const char *name)
{
	struct Name **pp = search(&name);

	if (*pp == (void *)name) /* entered name */
		*pp = new(Var, name);
	symbol = *pp;
	return (*pp)->token;
}

void install(const void *np)
{
	const char *name = ((struct Name *)np)->name;
	struct Name **pp = search(&name);

	if (*pp != (void *)name)
		error("cannot install name twice: %s", name);
	*pp = (struct Name *)np;
}

static void initNames(void)
{
    static const struct Name names[] = {
        {0, "let", LET},
        0 };
    const struct Name *np;

    for (np = names; np->name; ++np)
        install(np);
}