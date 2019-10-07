#ifndef PARSE_H
# define PARSE_H

enum tokens				
{
	NUMBER = '8',	/* literal constant */
	VAR = 'V',	/* variable */
};

void	error(const char *fmt, ...);

#endif
