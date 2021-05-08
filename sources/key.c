#include "minishell.h"

t_key	get_key(char c)
{
	if (c == 10)
		return (KEY_ENTER);
	if (c == 127)
		return (KEY_CANC);
	if (c == '\x1b')
	{
		read(0, &c, 1);
		if (c == '\x5b')
		{
			read(0, &c, 1);
			if (c == '\x41')
				return (KEY_UP);
			if (c == '\x42')
				return (KEY_DOWN);
			if (c == '\x43')
				return (KEY_RIGHT);
			if (c == '\x44')
				return (KEY_LEFT);
		}
	}
	return (KEY_NONE);
}

void	handle_enter(t_minishell *minishell)
{
	char	**single_input;
	int		i;

	if (minishell->input)
	{
		add_history(minishell, minishell->input);
		single_input = ft_split(minishell->input, ';');
		free(minishell->input);
		i = 0;
		while (single_input[i])
		{
			minishell->input = single_input[i++];
			parse_input(minishell);
			executor(minishell->command);
			free(minishell->input);
		}
		free(single_input);
		minishell->input = NULL;
	}
	minishell->cursor = 0;
	printf(CC_RESET "\n" CC_CYN "maxishell $> ");
}

void	handle_key(t_minishell *minishell, t_key key)
{
	int	tmp_len;

	tmp_len = 0;
	if (key == KEY_CANC) // TODO: non funzia con il cursore che non si trova al fondo dell'input
	{
		if (minishell->cursor == 0) //TODO: far partire un suono
			return;
		minishell->input[ft_strlen(minishell->input) - 1] = 0;
		printf("%c[2K", 27);
		printf("\r" CC_CYN "maxishell $> " CC_MAG "%s", minishell->input);
		minishell->cursor--;
	}
	else if (key == KEY_LEFT)
	{
		if (minishell->cursor == 0) //TODO: far partire un suono
			return;
		minishell->cursor--;
		printf("\033[1D"); //Muove il cursore uno slot indietro
	}
	else if (key == KEY_RIGHT)
	{
		if (minishell->cursor == ft_strlen(minishell->input)) //TODO: far partire un suono
			return;
		minishell->cursor++;
		printf("\033[1C"); //Muove il cursore uno slot avanti
	}
	else if (key == KEY_UP)
	{
		if (!(minishell->history->prec)) //TODO: far partire un suono
			return ;
		minishell->history = minishell->history->prec;
		if (minishell->input)
		{
			tmp_len = ft_strlen(minishell->input);
			free(minishell->input);
		}
		minishell->input = ft_strdup(minishell->history->cmd_line);
	}
	else if (key == KEY_DOWN)
	{
		if (!(minishell->history->next)) //TODO: far partire un suono
			return ;
		minishell->history = minishell->history->next;
		if (minishell->input)
		{
			tmp_len = ft_strlen(minishell->input);
			free(minishell->input);
		}
		minishell->input = ft_strdup(minishell->history->cmd_line);
	}
	if (key == KEY_UP || key == KEY_DOWN)
	{
		printf("%c[2K", 27);
		printf("\r" CC_CYN "maxishell $> " CC_MAG "%s", minishell->input);
		minishell->cursor = ft_strlen(minishell->input);
	}
}