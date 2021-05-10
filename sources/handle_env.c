#include "minishell.h"

void	handle_env(t_minishell *minishell)
{
	t_list	*tmp;

	printf(CC_RESET);
	tmp = minishell->main_env;
	while (tmp)
	{
		printf("%s\n", (char *)tmp->data);
		tmp = tmp->next;
	}
}