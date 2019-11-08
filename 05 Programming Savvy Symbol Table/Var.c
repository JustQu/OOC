#include "Var.h"
#include "value.r"
#include "parse.h"
#include "Name.h"
#include "Name.r"

#include <stdlib.h>
#include <assert.h>
#include <string.h>

struct Var { struct Name _; double value; };

#define value(tree) (((struct Var *)tree)->value)

static double doVar(const void *tree)
{
	return value(tree);
}

static void freeVar(void *tree)
{
}

static void *mkVar(va_list ap)
{
	struct Var *node = calloc(1, sizeof(struct Var));
	const char *name = va_arg(ap, const char *);
	size_t len = strlen(name);

	assert(node);
	node->_.name = malloc(len + 1);
	assert(node->_.name);
	strcpy((void *)node->_.name, name);
	node->_.token = VAR;
	return node;
}

static struct Type _Var = {mkVar, doVar, freeVar};

const void *Var = &_Var;

static double doAssign(const void *tree)
{
	return value(left(tree)) = exec(right(tree));
}

static struct Type _Assign = { mkBin, doAssign, freeBin };

const void *Assign = &_Assign;
