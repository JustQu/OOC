#include <setjmp.h>
#include <errno.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include "parse.h"	/* defines NUMBER */

static enum tokens	token;	/* current input symbol */
static double		number; /* if NUMBER: numerical value */

static jmp_buf	onError;

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
			error("bad value: %s", strerror(error));
	}
	else
		token = *bp ? *bp++ : 0;
	return token;
}

/*
** sum : product { +|— product }...
*/
void	sum(void)
{
	product();
	for(;;)
	{
		switch(token)
		{
			case '+':
			case '-':
				scan(0), product(); continue;
		}
		return;
	}
}

int		main(void)
{
	volatile int	errors = 0;
	char			buf[BUFSIZ];

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