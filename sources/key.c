#include "minishell.h"

t_key	get_key(char c)
{
	if (c == 10)
		return (KEY_ENTER);
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

void	handle_key(t_minishell *minishell, t_key key)
{
	if (key == KEY_LEFT)
	{
		if (minishell->cursor == 0)
			return;
		minishell->cursor--;
		printf("\033[1D");
	}
	else if (key == KEY_RIGHT)
	{
		if (minishell->cursor == ft_strlen(minishell->input))
			return;
		minishell->cursor++;
		printf("\033[1C");
	}
	else if (key == KEY_ENTER)
	{
		//TODO: parser, executor using "minishell->input"
		if (minishell->input)
		{
			free(minishell->input);
			minishell->input = NULL;
		}
		minishell->cursor = 0;
		printf(CC_RESET "\n" CC_CYN "maxishell $> ");
	}
}