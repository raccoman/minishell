#include "minishell.h"

void	handle_echo(t_minishell *minishell, t_simple_cmd *curr)
{
	int		i;
	int		n_flag;
	int		length;
	char	**args;

	args = &(curr->arguments[1]);
	i = 0;
	n_flag = 0;
	if (*args && !ft_strcmp("-n", *args))
		n_flag = ++i;
	if (n_flag)
	{
		if (minishell->prompt)
			free(minishell->prompt);
		minishell->prompt = ft_strmaxjoin(&(args[1]), " ");
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