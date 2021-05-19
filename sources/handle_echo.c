#include "minishell.h"

short	is_option_n(char *str)
{
	if (*str++ != '-')
		return (0);
	return (ft_onlythischar(str, 'n'));
}

void	handle_echo(t_minishell *minishell, t_simple_cmd *curr)
{
	int		i;
	int		n_flag;
	int		length;
	char	**args;

	args = &(curr->arguments[1]);
	i = 0;
	n_flag = 0;
	while (args[i] && is_option_n(args[i]))
		n_flag = ++i;
	if (n_flag)
	{
		if (minishell->prompt)
			free(minishell->prompt);
		minishell->prompt = ft_strmaxjoin(&(args[i]), " ");
		return ;
	}
	while (args[i] && args[i + 1])
		printf("%s ", args[i++]);
	length = ft_strlen(args[i]);
	if (!length)
		printf("\n");
	else
		printf("%s\n", args[i]);
}
