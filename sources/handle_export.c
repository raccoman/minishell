#include "minishell.h"

void	single_export(t_minishell *minishell, char *export)
{
	t_list	*env;

	if (is_assign(export))
		single_assign(minishell, export);
	env = find_env(minishell->main_env, export);
	if (env)
		return ;
	env = find_env(minishell->session_env, export);
	if (env)
	{
		ft_lstadd_back(&minishell->main_env, ft_lstnew(ft_strdup(env->data)));
		ft_lstrmv_if(&minishell->session_env, export, &cmd_cmp, &free);
	}
}

void	handle_export(t_minishell *minishell, t_simple_cmd *curr)
{
	int 	i;
	char 	**args;

	args = &(curr->arguments[1]);
	// todo export senza argomenti
	if (!args[0])
	{
		printf(CC_WHT "export: " CC_RED "not enough arguments" CC_RESET "\n");
		return ;
	}
	i = 0;
	while (args[i])
		single_export(minishell, args[i++]);
}