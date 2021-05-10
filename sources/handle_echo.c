#include "minishell.h"

void	handle_echo(t_simple_cmd *curr)
{
	int	i;
	int	n_flag;
	int	length;
	char	**args;

	args = &(curr->arguments[1]);
	i = 0;
	n_flag = 0;
	if (!args[i])
	{
		printf("\n");
		return ;
	}
	if (ft_strcmp("-n", args[i]) == 0)
		n_flag = ++i;
	if (!args[i] && n_flag)
	{
		printf("");
		return ;
	}
	printf(CC_RESET);
	while (args[i] && args[i + 1])
		printf("%s ", args[i++]);
	length = ft_strlen(args[i]);
	if (args[i][length - 1] == '\n' && n_flag)
		printf("%.*s", length - 1, args[i]);
	else if (n_flag)
		printf("%s", args[i]);
	else
		printf("%s\n", args[i]);
	return ;
}