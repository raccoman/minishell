#include "minishell.h"

t_key	get_key(char c)
{
	if (c == '\x10')
		return (KEY_CTRL_P);
	if (c == '\x18')
		return (KEY_CTRL_X);
	if (c == '\x15')
		return (KEY_CTRL_U);
	if (c == 0x4)
		return (KEY_EOF);
	if (c == 9)
		return (KEY_TAB);
	if (c == 10)
		return (KEY_ENTER);
	if (c == 127)
		return (KEY_CANCEL);
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

void	adjust_prompt(t_minishell *minishell)
{
	static char	*old_promt;

	if (minishell->prompt)
	{
		if (!old_promt)
			old_promt = minishell->prompt;
		else
		{
			if (minishell->prompt == old_promt)
			{
				free(minishell->prompt);
				minishell->prompt = NULL;
				old_promt = NULL;
			}
			else
				old_promt = minishell->prompt;
		}
	}
}

void	handle_enter(t_minishell *minishell)
{
	char	**single_input;
	int		i;
	static	int n_flag;

	printf(CC_RESET "\n");
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
			executor(minishell, minishell->command);
			free(minishell->input);
		}
		free(single_input);
		minishell->input = NULL;
	}
	minishell->cursor = 0;
	adjust_prompt(minishell);
	prompt(minishell, "");
}

void	handle_key(t_minishell *minishell, t_key key)
{
	int	i;

	if (key == KEY_CTRL_X) // Cut
	{
		if (minishell->input && *minishell->input)
		{
			minishell->clipboard = ft_strdup(minishell->input + minishell->cursor);
			minishell->input[minishell->cursor] = 0;
			prompt(minishell, "\r");
			return ;
		}
		printf("\a");
		return ;
	}
	if (key == KEY_CTRL_P) //Paste
	{
		if (minishell->clipboard)
		{
			i = -1;
			while (minishell->clipboard[++i])
			{
				minishell->input = ft_insert(minishell->input, minishell->clipboard[i], minishell->cursor);
				minishell->cursor++;
			}
			prompt(minishell, "\r");
			return ;
		}
		printf("\a");
		return ;
	}
	if (key == KEY_CTRL_U) //Copy
	{
		if (minishell->input && *minishell->input)
		{
			minishell->clipboard = ft_strdup(minishell->input + minishell->cursor);
			return ;
		}
		printf("\a");
		return ;
	}
	if (key == KEY_EOF && (!minishell->input || !*minishell->input))
	{
		printf("exit\n");
		handle_exit(minishell);
		return ;
	}
	if (key == KEY_CANCEL)
	{
		if (minishell->cursor == 0)
		{
			printf("\a");
			return;
		}
		minishell->cursor--;
		minishell->input = ft_remove_at(minishell->input, minishell->cursor);
		prompt(minishell, "\r");
	}
	else if (key == KEY_LEFT)
	{
		if (minishell->cursor == 0)
		{
			printf("\a");
			return;
		}
		minishell->cursor--;
		//printf("\033[1D"); //Muove il cursore uno slot indietro
		printf("\b");
	}
	else if (key == KEY_RIGHT)
	{
		if (minishell->cursor == ft_strlen(minishell->input))
		{
			printf("\a");
			return;
		}
		minishell->cursor++;
		printf("\033[1C"); //Muove il cursore uno slot avanti
	}
	else if (key == KEY_UP)
	{
		if (!(minishell->history->prec))
		{
			printf("\a");
			return;
		}
		minishell->history = minishell->history->prec;
		if (minishell->input)
		{
			free(minishell->input);
		}
		minishell->input = ft_strdup(minishell->history->cmd_line);
	}
	else if (key == KEY_DOWN)
	{
		if (!(minishell->history->next))
		{
			printf("\a");
			return;
		}
		minishell->history = minishell->history->next;
		if (minishell->input)
		{
			free(minishell->input);
		}
		minishell->input = ft_strdup(minishell->history->cmd_line);
	}
	if (key == KEY_UP || key == KEY_DOWN)
	{
		minishell->cursor = ft_strlen(minishell->input);
		prompt(minishell, "\r");
	}
}