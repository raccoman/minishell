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
	init_history(minishell);
	minishell->input = NULL;
	minishell->cursor = 0;
	configure_termios(minishell);
	minishell->command = malloc(sizeof(t_command));
	minishell->command->infile = NULL;
	minishell->command->outfile = NULL;
	minishell->command->append = 0;
	minishell->command->s_commands = NULL;
}

void	terminate(t_minishell *minishell)
{
	clear_history(minishell->history);
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
			printf("\r" CC_CYN "maxishell $> " CC_MAG "%s", minishell->input); //Questo a spostato alla fine il cursore
			update_cursor(minishell); //Incremento cursor, e lo rimetto nella giusta posizione
		}
		ft_fflush(stdout);
	}
}
