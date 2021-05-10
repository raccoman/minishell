#include "minishell.h"

void    clear_all(t_minishell *minishell)
{
    free(minishell->input);
    clear_history(minishell->history);
    clear_commands(minishell->command);
    ft_lstclear(&minishell->main_env);
    ft_lstclear(&minishell->session_env);
}

void    handle_exit(t_minishell *minishell)
{
	printf(CC_WHT "Bye bye\n" CC_RESET);
    clear_all(minishell);
	exit(0);
}
