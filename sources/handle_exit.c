#include "minishell.h"

void	clear_all(t_minishell *minishell)
{
	free(minishell->input);
	free(minishell->prompt);
	free(minishell->clipboard);
	clear_history(minishell->history);
	clear_commands(minishell->command);
	ft_lstclear(&minishell->main_env);
	ft_lstclear(&minishell->session_env);
	ft_lstclear(&minishell->exported);
	free(minishell);
}

void	handle_exit(t_minishell *minishell, t_simple_cmd *curr)
{
	char	**args;
	char	*prefix;
	int		exit_value;

	exit_value = ft_atoi(get_env_value(minishell, "?"));
	if (curr && curr->arguments[1])
	{
		args = &(curr->arguments[1]);
		if (!ft_is_num(*args))
		{
			prefix = ft_strjoin("exit: ", *args);
			print_error(prefix, "numeric argument required");
			free(prefix);
			exit_value = 1;
		}
		else
			exit_value = ft_atoi(*args);
	}
	printf(CC_WHT "Bye bye" CC_RESET "\n");
	clear_all(minishell);
	exit((exit_value + 256) % 256);
}
