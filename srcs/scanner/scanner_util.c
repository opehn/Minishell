#include "env.h"
#include "scanner.h"
#include "tree.h"
#include "error.h"
#include "parsing.h"
#include "libft.h"

#include <stdio.h>

void	ignore_space(char *data, int *i)
{
	if (data[*i] == ' ')
	{
		while(data[*i] == ' ')
			(*i)++;
	}
}

void	init_str(char **str)
{
	*str = malloc(1);
	*str[0]= '\0';
}

void	pass_sign(int type, int *i)
{
	if (type <= 2) 
		(*i) += 1;
	else if (type <= 4)
		(*i) += 2;
}