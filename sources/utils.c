#include "minishell.h"

void	print_error(char *formatted, char *arg)
{
	int	tmpout;

	tmpout = dup(1);
	dup2(2, 1);
	if (arg)
		printf(formatted, arg);
	else
		printf("%s", formatted);
	dup2(tmpout, 1);
	close(tmpout);
}

int is_path(char *str)
{
	while (*str)
	{
		if (*str++ == '/')
			return (1);
	}	
	return (0);
}

/*int	is_empty(char **args)
{
	int	k;

	if (!args[0])
		return (1);
	k = 0;
	while (args[0][k])
	{
		if (!ft_isspace(args[0][k]))
			return (0);
		k++;
	}
	return (1);
}*/

short	is_option(char *str)
{
	if (*str == '-')
		return (1);
	return (0);
}