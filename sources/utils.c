#include "minishell.h"

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

int	is_assign(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (i && str[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

int	is_path(char *str)
{
	while (*str)
	{
		if (*str++ == '/')
			return (1);
	}	
	return (0);
}

short	check_option(char *cmd, char *first)
{
	char	*error_prefix;

	if (first && *first == '-')
	{
		error_prefix = ft_strjoin(cmd, first);
		print_error(error_prefix, "Invalid option");
		free(error_prefix);
		return (0);
	}
	return (1);
}
