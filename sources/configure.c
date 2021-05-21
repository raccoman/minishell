#include "minishell.h"

void	configure_termios(t_minishell *minishell)
{
	tcgetattr(0, &minishell->sys_cfg);
	ft_memcpy(&minishell->our_cfg, &minishell->sys_cfg, sizeof(struct termios));
	minishell->our_cfg.c_lflag &= ~(ECHO | ICANON);
	minishell->our_cfg.c_cc[VMIN] = 1;
	minishell->our_cfg.c_cc[VTIME] = 0;
}

void	configure_env(t_minishell *minishell, char	**env)
{
	minishell->main_env = NULL;
	while (*env)
	{
		ft_lstadd_back(&minishell->main_env, ft_lstnew(ft_strdup(*env)));
		env++;
	}
	minishell->session_env = NULL;
	single_assign(minishell, ft_strdup("?=0"));
	minishell->exported = NULL;
}

void	init_history(t_minishell *minishell)
{
	t_history	*tmp;

	tmp = malloc(sizeof(t_history));
	tmp->cmd_line = ft_strdup("");
	tmp->safe = ft_strdup("");
	tmp->next = NULL;
	tmp->prec = NULL;
	minishell->history = tmp;
}

void	configure(t_minishell *minishell, char **env)
{
	configure_env(minishell, env);
	minishell->running = 1;
	init_history(minishell);
	minishell->clipboard = NULL;
	minishell->prompt = NULL;
	minishell->input = NULL;
	minishell->semicols = NULL;
	minishell->cursor = 0;
	configure_termios(minishell);
	minishell->command = malloc(sizeof(t_command));
	minishell->command->infile = NULL;
	minishell->command->outfile = NULL;
	minishell->command->append = 0;
	minishell->command->here_doc = 0;
	minishell->command->s_commands = NULL;
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, handle_sigquit);
	minishell->pid = -1;
}
