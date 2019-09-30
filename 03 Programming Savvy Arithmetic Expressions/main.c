#include <setjmp.h>
#include <errno.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include "parse.h"	/* defines NUMBER */
#include "value.h"

static enum tokens	token;	/* current input symbol */
static double		number; /* if NUMBER: numerical value */

static enum tokens	scan(const char *buf)	/* return token = next input symbol */
{
	static const char	*bp;

	if (buf)
		bp = buf;	/* new input line */
	
	while (isspace(*bp))
		bp++;
	if (isdigit(*bp) || *bp == '.')
	{
		errno = 0;
		token = NUMBER, number = strtod(bp, (char **)&bp);
		if (errno == ERANGE)
			error("bad value: %s", strerror(errno));
	}
	else
		token = *bp ? *bp++ : 0;
	return token;
}

static void	*sum(void);

/*
** factor: +factor
**					-factor
**					NUMBER
**					( sum )
*/

static void	*factor(void)
{
	void	*result;

	switch ((int)token)
	{
		case '+':
			scan(0);
			return factor();
		case '-':
			scan(0);
			return (new(Minus, factor()));
		default:
			error("bad factor: '%c' 0x%x", token, token);
		case NUMBER:
			result = new(Value, number);
			break;
		case '(':
			scan(0);
			result = sum();
			if (token != ')')
				error("expecting )");
	}
	scan(0);
	return result;
}

/*
** product: factor { *|/ factor }...
*/

static void *product(void)
{
	void		*result = factor();
	const void	*type;

	for (;;)
	{
		switch((int)token)
		{
			case '*':
				type = Mult;
				break;
			case '/':
				type = Div;
				break;
			default:
				return (result);
		}
		scan(0);
		result = new(type, result, factor());
	}
}

/*
** sum : product { +|— product }...
*/
static void	*sum(void)
{
	void		*result = product();
	const void	*type;

	for(;;)
	{
		switch((int)token)
		{
			case '+':
				type = Add;
				break;
			case '-':
				type = Sub;
				break;
			default:
				return result;
		}
		scan(0);
		result = new(type, result, product());
	}
}

static jmp_buf	onError;

#include <stdint.h>

int		main(void)
{
	volatile int	errors = 0;
	char			buf[BUFSIZ];

	size_t g;
	printf("%u", SIZE_MAX);
	if (setjmp(onError))
		++errors;

	while (gets(buf))
		if (scan(buf))
		{
			void	*e = sum();

			if (token)
				error("trash afer sum");
			process(e);
			delete(e);
		}
	return errors > 0;
}

void	error(const char *fmt, ...)
{
	va_list	ap;

	va_start(ap, fmt);
	vfprintf(stderr, fmt, ap), putc('\n', stderr);
	va_end(ap);
	longjmp(onError, 1);
}