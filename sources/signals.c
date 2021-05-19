#include "minishell.h"

void	handle_sigint(int signal)
{
	(void)signal;
	if (!g_minishell->pid)
		exit(0);
	if (g_minishell->input)
		free(g_minishell->input);
	if (g_minishell->prompt)
		free(g_minishell->prompt);
	g_minishell->cursor = 0;
	g_minishell->prompt = NULL;
	g_minishell->input = NULL;
	if (g_minishell->pid == -1)
	{
		printf("\n");
		prompt(g_minishell, "\r");
	}
	else
		printf("\n");
	ft_fflush(stdout);
}

void	handle_sigquit(int signal)
{
	(void)signal;
	if (g_minishell->pid != -1)
	{
		printf(CC_RED "Quit: 3" CC_RESET "\n" CC_MAG);
		ft_fflush(stdout);
	}
}
