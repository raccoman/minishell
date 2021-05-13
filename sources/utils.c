#include "minishell.h"

/*void	print_error(char *formatted, char *arg)
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
}*/

void	print_error(char *prefix, char *error_msg)
{
	int		tmpout;
	int		do_free;

	single_assign(g_minishell, ft_strdup("?=1"));
	tmpout = dup(1);
	dup2(2, 1);
	do_free = 0;
	if (errno == ENOENT && !is_path(prefix))
	{
		do_free++;
		error_msg = ft_strdup("Command not found");
	}
	printf(CC_RESET "%s:" CC_RED " %s" CC_RESET "\n", prefix, error_msg);
	dup2(tmpout, 1);
	close(tmpout);
	if (do_free)
		free(error_msg);
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

char	get_last_char(int fd)
{
	char	prev;
	char	c;

	while (read(fd, &c, 1) > 0)
		prev = c;
	return (prev);
}