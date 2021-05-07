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

void	configure(t_minishell *minishell, char *env[])
{
	minishell->main_env = env;
	minishell->running = 1;
	minishell->input = NULL;
	minishell->cursor = 0;
	configure_termios(minishell);
}

void	terminate(t_minishell *minishell)
{
	if (minishell->input)
	{
		free(minishell->input);
		minishell->input = NULL;
	}
}

void	update_cursor(t_minishell *minishell)
{
	int	length;

	minishell->cursor++;
	length = ft_strlen(minishell->input);
	while (minishell->cursor < length)
	{
		printf("\033[1D");
		length--;
	}
}

void	get_input(t_minishell *minishell)
{
	char	c;
	t_key	key;

	read(0, &c, 1);
	key = get_key(c);
	if (key != KEY_NONE)
	{
		handle_key(minishell, key);
		return;
	}
	minishell->input = ft_insert(minishell->input, c, minishell->cursor);
	printf("\r" CC_CYN "maxishell $> " CC_MAG "%s", minishell->input);
	update_cursor(minishell);
}
