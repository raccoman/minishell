#include "minishell.h"

t_key	get_key(char c)
{
	if (c >= 32 && c <= 126)
		return (KEY_ALPHANUMERIC);
	if (c == '\x10')
		return (KEY_CTRL_P);
	if (c == '\x18')
		return (KEY_CTRL_X);
	if (c == '\x15')
		return (KEY_CTRL_U);
	if (c == '\x04')
		return (KEY_EOF);
	if (c == '\x09')
		return (KEY_TAB);
	if (c == '\x0a')
		return (KEY_ENTER);
	if (c == '\x7f')
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
			if (c == '\x48')
				return (KEY_HOME);
			if (c == '\x46')
				return (KEY_END);
			if (c == '\x31')
			{
				read(0, &c, 1);
				if (c == '\x3b')
				{
					read(0, &c, 1);
					if (c == '\x32')
					{
						read(0, &c, 1);
						if (c == '\x41')
							return (KEY_SHIFT_UP);
						if (c == '\x42')
							return (KEY_SHIFT_DOWN);
						if (c == '\x44')
							return (KEY_SHIFT_LEFT);
						if (c == '\x43')
							return (KEY_SHIFT_RIGHT);
					}
				}
			}
		}
	}
	return (KEY_UNKNOWN);
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

int	first_check(t_minishell *minishell, char *input)
{
	int	ret;
	int check;

	ret = 1;
	if (!input)
		ret = 0;
	else
	{
		check = check_quote(minishell->input);
		if (!check || check == -1)
		{
			add_history(minishell, minishell->input);
			free(minishell->input);
			minishell->input = NULL;
			if (!check)
				print_error("syntax error", "missing quote");
			else
				print_error("syntax error", "escape at the end of line");
			ret = check;
			if (ret == -1)
				ret = 0;
		}
	}
	if (ret)
		return (ret);
	minishell->cursor = 0;
	adjust_prompt(minishell);
	prompt(minishell, "");
	return (ret);
}

void	handle_enter(t_minishell *minishell)
{
	char	**single_input;
	int		i;
	static	int n_flag;

	printf(CC_RESET "\n");
	if (!first_check(minishell, minishell->input))
		return ;
	if (minishell->input)
	{
		add_history(minishell, minishell->input);
		single_input = safe_split(minishell->input, ';');
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

	if (key == KEY_HOME)
	{
		if (minishell->cursor == 0)
		{
			printf("\a");
			return ;
		}
		while (minishell->cursor > 0)
		{
			minishell->cursor--;
			printf("\033[1D");
		}
		return ;
	}
	if (key == KEY_END)
	{
		i = ft_strlen(minishell->input);
		if (minishell->cursor == i)
		{
			printf("\a");
			return ;
		}
		while (minishell->cursor < i)
		{
			minishell->cursor++;
			printf("\033[1C");
		}
		return ;
	}
	if (key == KEY_CTRL_X) // Cut
	{
		if (minishell->input && *minishell->input)
		{
			minishell->clipboard = ft_strdup(minishell->input + minishell->cursor);
			minishell->input[minishell->cursor] = 0;
			update_history(minishell->history, minishell->input);
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
				update_history(minishell->history, minishell->input);
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
	if (key == KEY_EOF)
	{
		if (!minishell->input || !*minishell->input)
		{
			printf("exit\n");
			handle_exit(minishell, NULL);
		}
		else
			printf("\a");
			
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
		update_history(minishell->history, minishell->input);
		prompt(minishell, "\r");
	}
	if (key == KEY_SHIFT_LEFT)
	{
		if (minishell->cursor == 0)
		{
			printf("\a");
			return;
		}
		while (minishell->cursor > 0 && minishell->input[minishell->cursor] != ' ')
		{
			minishell->cursor--;
			printf("\033[1D");
		}
		while (minishell->cursor > 0 && minishell->input[minishell->cursor] == ' ')
		{
			minishell->cursor--;
			printf("\033[1D");
		}
		while (minishell->cursor > 0 && minishell->input[minishell->cursor] != ' '
			&& minishell->input[minishell->cursor - 1] != ' ')
		{
			minishell->cursor--;
			printf("\033[1D");
		}
		return ;
	}
	if (key == KEY_LEFT)
	{
		if (minishell->cursor == 0)
		{
			printf("\a");
			return;
		}
		minishell->cursor--;
		printf("\033[1D"); //Muove il cursore uno slot indietro
	}
	if (key == KEY_SHIFT_RIGHT)
	{
		i = ft_strlen(minishell->input);
		if (minishell->cursor == i)
		{
			printf("\a");
			return;
		}
		while (minishell->cursor < i && minishell->input[minishell->cursor] != ' ')
		{
			minishell->cursor++;
			printf("\033[1C");
		}
		while (minishell->cursor < i && minishell->input[minishell->cursor] == ' ')
		{
			minishell->cursor++;
			printf("\033[1C");
		}
		return ;
	}
	if (key == KEY_RIGHT)
	{
		if (minishell->cursor == ft_strlen(minishell->input))
		{
			printf("\a");
			return;
		}
		minishell->cursor++;
		printf("\033[1C"); //Muove il cursore uno slot avanti
	}
	if (key == KEY_UP || key == KEY_SHIFT_UP)
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
	if (key == KEY_DOWN || key == KEY_SHIFT_DOWN)
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
	if (key == KEY_SHIFT_DOWN || key == KEY_SHIFT_UP)
	{
		if (minishell->cursor >= ft_strlen(minishell->input))
			minishell->cursor = ft_strlen(minishell->input);
		prompt(minishell, "\r");
	}
}