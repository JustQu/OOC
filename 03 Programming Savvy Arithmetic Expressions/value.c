#include <stdarg.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

#include "value.h"
#include "parse.h"

struct Type
{
	void	*(*new)(va_list ap);
	double	(*exec)(const void *tree);
	void	(*delete)(void *tree);
};

void	*new(const void *type, ...)
{
	va_list	ap;
	void	*result;

	assert(type && ((struct Type *)type)->new);
	va_start(ap, type);
	result = ((struct Type *)type)->new(ap);
	*(const struct Type **)result = type;
	va_end(ap);
	return result;
}

static double	exec(const void *tree)
{
	assert(tree && *(struct Type **)tree
			&& (*(struct Type **)tree)->exec);
	
	return (*(struct Type **)tree)->exec(tree);
}

void		process(const void *tree)
{
	printf("\t%g\n", exec(tree));
}

void		delete(void *tree)
{
	assert(tree && *(struct Type **)tree
			&& (*(struct Type **)tree)->delete);

	(*(struct Type **)tree)->delete(tree);
}

struct	Bin
{
	const void	*type;
	void		*left;
	void		*right;
};

static void *mkBin(va_list ap)
{
	struct Bin	*node = malloc(sizeof(struct Bin));

	assert (node);
	node->left = va_arg(ap, void *);
	node->right = va_arg(ap, void *);
	return node;
}

static double	doAdd(const void *tree)
{
	return exec(((struct Bin *)tree)->left) +
			exec(((struct Bin *)tree)->right);
}

static double	doSub(const void *tree)
{
	return exec(((struct Bin *)tree)->left) -
			exec(((struct Bin *)tree)->right);
}

static double	doMult(const void *tree)
{
	return exec(((struct Bin *)tree)->left) *
			exec(((struct Bin *)tree)->right);
}
static double	doDiv(const void *tree)
{
	double	right = exec(((struct Bin *)tree)->right);

	if (right == 0.0)
		error("division by zero");
	return exec(((struct Bin *)tree)->left) /
			right;
}

static void	freeBin(void *tree)
{
	delete(((struct Bin *)tree)->left);
	delete(((struct Bin *)tree)->right);
	free(tree);
}

static struct Type _Add = {mkBin, doAdd, freeBin};
static struct Type _Sub = { mkBin, doSub, freeBin};
static struct Type _Mult = { mkBin, doMult, freeBin};
static struct Type _Div = { mkBin, doDiv, freeBin};

const void  *Add = &_Add;
const void  *Sub = &_Sub;
const void  *Mult = &_Mult;
const void  *Div = &_Div;

struct	Val
{
	const void  *type;
	double		value;
};

static void	*mkVal(va_list ap)
{
	struct Val	*node = malloc(sizeof(struct Val));

	assert(node);
	node->value = va_arg(ap, double);
	return node;
}

static double	doVal(const void *tree)
{
	return ((struct Val *)tree)->value;
}

static struct Type	_Value = {"", mkVal, doVal, free};

const void  *Value = &_Value;

struct	Unary
{
	const void  *type;
	void		*next;
};

static void *mkUnary(va_list ap)
{
	struct Unary	*node = malloc(sizeof(struct Unary));

	assert(node);
	node->next = va_arg(ap, void *);
	return node;
}

static double	doUnary(const void *tree)
{
	return -exec(((struct Unary *)tree)->next);
}

static void	freeUnary(void *tree)
{
	delete(((struct Unary *)tree)->next);
	free(tree);
}

static struct Type	_Minus = {mkUnary, doUnary, freeUnary};

const void  *Minus = &_Minus;