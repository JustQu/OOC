#ifndef PARSE_H
# define PARSE_H

enum tokens				
{
	NUMBER = 'n',	/* literal constant */
	VAR = 'v',		/* variable */
	LET = 'l',	
};

void	error(const char *fmt, ...);

#endif
