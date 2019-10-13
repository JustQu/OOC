#include "Name.h"
#include "Name.r"

#include "parse.h"

static void initNames(void)
{
    static const struct Name names[] = {
        {0, "let", LET},
        0 };
    const struct Name *np;
    for (np = names; np->name; ++np)
        install(np);
}