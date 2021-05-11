#include "minishell.h"

void	configure_termios(t_minishell *minishell)
{
	tcgetattr(0, &minishell->sys_cfg);
	tcgetattr(0, &minishell->our_cfg);
	minishell->our_cfg.c_iflag &= ~(IXON);
	minishell->our_cfg.c_lflag &= ~(ECHO | ICANON |IEXTEN);
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
}

void	handle_signal(int signal)
{
	(void)signal;
	g_minishell->cursor = 0;
	if (g_minishell->input)
		free(g_minishell->input);
	g_minishell->input = NULL;
	if (g_minishell->prompt)
	{
		free(g_minishell->prompt);
		g_minishell->prompt = NULL;
	}
	printf("\n" CC_CYN "maxishell $> " CC_MAG);
	ft_fflush(stdout);
}

void	configure(t_minishell *minishell, char **env)
{
	configure_env(minishell, env);
	minishell->running = 1;
	init_history(minishell);
	minishell->prompt = NULL;
	minishell->input = NULL;
	minishell->cursor = 0;
	configure_termios(minishell);
	minishell->command = malloc(sizeof(t_command));
	minishell->command->infile = NULL;
	minishell->command->outfile = NULL;
	minishell->command->append = 0;
	minishell->command->s_commands = NULL;
	signal(SIGINT, handle_signal);
}

void	terminate(t_minishell *minishell)
{
	clear_history(minishell->history);
	if (minishell->input)
	{
		free(minishell->input);
		minishell->input = NULL;
	}
	free(minishell);
}

void	get_input(t_minishell *minishell)
{
	char	c;
	t_key	key;

	while (1)
	{
		tcsetattr(0, TCSAFLUSH, &minishell->our_cfg);
		read(0, &c, 1);
		key = get_key(c);
		tcsetattr(0, TCSAFLUSH, &minishell->sys_cfg);
		if (key == KEY_ENTER)
			break ;
		if (key != KEY_NONE)
			handle_key(minishell, key);
		else
		{
			minishell->input = ft_insert(minishell->input, c, minishell->cursor);
			minishell->cursor++;
			prompt(minishell, "\r");
		}
		ft_fflush(stdout);
	}
}
