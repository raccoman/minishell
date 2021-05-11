#include "minishell.h"

// TODO: con opzione -n sbarella di brutto

void	handle_echo(t_minishell *minishell, t_simple_cmd *curr)
{
	int	i;
	int	n_flag;
	int	length;
	char	**args;

	args = &(curr->arguments[1]);
	i = 0;
	n_flag = 0;
	if (ft_strcmp("-n", args[i]) == 0)
		n_flag = ++i;
	while (args[i] && args[i + 1])
		printf("%s ", args[i++]);
	length = ft_strlen(args[i]);
	if (length == 0 && n_flag)
		printf("");
	else if (length == 0)
		printf("\n");
	else if (args[i][length - 1] == '\n' && n_flag)
		printf("%.*s", length - 1, args[i]);
	else if (n_flag)
		printf("%s", args[i]);
	else
		printf("%s\n", args[i]);
	return ;
}