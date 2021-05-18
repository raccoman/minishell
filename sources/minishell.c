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

void	handle_signal(int signal)
{
	if (!g_minishell->pid)
			exit(0);
	if (signal == SIGINT)
	{
		if (!g_minishell->quotes.done)
		{
			g_minishell->quotes.done = 1;
			g_minishell->quotes.input = ft_strdup("");
			g_minishell->quotes.cursor = 0;
			write(0, " ", 1);
		}
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
	else if (signal == SIGQUIT && (g_minishell->pid != -1))
	{
		printf(CC_RED "Quit: 3" CC_RESET "\n" CC_MAG);
		ft_fflush(stdout);
	}
}

void	configure(t_minishell *minishell, char **env)
{
	configure_env(minishell, env);
	minishell->running = 1;
	init_history(minishell);
	minishell->clipboard = NULL;
	minishell->prompt = NULL;
	minishell->input = NULL;
	minishell->cursor = 0;
	configure_termios(minishell);
	minishell->command = malloc(sizeof(t_command));
	minishell->command->infile = NULL;
	minishell->command->outfile = NULL;
	minishell->command->append = 0;
	minishell->command->here_doc = 0;
	minishell->command->s_commands = NULL;
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, handle_signal);
	reset_quote(minishell);
	minishell->pid= -1;
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
	
	minishell->pid = -1;
	while (1)
	{
		tcsetattr(0, TCSANOW, &minishell->our_cfg);
		read(0, &c, 1);
		key = get_key(c);
		tcsetattr(0, TCSANOW, &minishell->sys_cfg);
		if (key == KEY_ENTER)
		{
			//if (check_quote(minishell))
			break ;
			/*minishell->quotes.input = ft_strdup(minishell->input);
			minishell->quotes.cursor = minishell->cursor;
			minishell->input = NULL;
			minishell->cursor = 0;
			get_input_quote(minishell);
			minishell->input = ft_strdup(minishell->quotes.input);
			minishell->cursor = minishell->quotes.cursor;
			break ;*/
		}
		else if (key != KEY_ALPHANUMERIC)
			handle_key(minishell, key);
		else
		{
			calculate_quote(minishell, c);
			minishell->input = ft_insert(minishell->input, c, minishell->cursor);
			update_history(minishell->history, minishell->input);
			minishell->cursor++;
			prompt(minishell, "\r");
		}
		ft_fflush(stdout);
	}
}
