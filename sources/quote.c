#include "minishell.h"

void	reset_quote(t_minishell *minishell)
{
	minishell->quotes.done = 1;
	minishell->quotes.a = 0;
	minishell->quotes.b = 0;
	if (minishell->quotes.input)
		free(minishell->quotes.input);
	minishell->quotes.input = NULL;
	minishell->quotes.cursor = 0;
}

void	calculate_quote(t_minishell *minishell, char c)
{
	if (c == '\'')
		minishell->quotes.a = !minishell->quotes.a;
	if (c == '\"')
		minishell->quotes.b = !minishell->quotes.b;
}

int	check_quote(t_minishell *minishell)
{
	return (!minishell->quotes.a && !minishell->quotes.b);
}

void	get_input_quote(t_minishell *minishell)
{
	char	c;
	t_key	key;

	minishell->quotes.done = 0;
	minishell->quotes.input = ft_append(minishell->quotes.input, '\n');
	minishell->quotes.cursor++;
	printf(CC_RESET "\n" CC_CYN "> " CC_MAG);
	ft_fflush(stdout);
	while (!minishell->quotes.done)
	{
		tcsetattr(0, TCSANOW, &minishell->our_cfg);
		read(0, &c, 1);
		key = get_key(c);
		tcsetattr(0, TCSANOW, &minishell->sys_cfg);
		if (key == KEY_ENTER)
		{
			minishell->quotes.input = ft_strjoin(minishell->quotes.input, minishell->input);
			minishell->quotes.cursor += minishell->cursor;
			minishell->input = NULL;
			minishell->cursor = 0;
			if (check_quote(minishell))
			{
				minishell->quotes.done = 1;
				break;
			}
			get_input_quote(minishell);
			break ;
		}
		else if (key != KEY_ALPHANUMERIC)
			handle_key(minishell, key);
		else
		{
			calculate_quote(minishell, c);
			minishell->input = ft_insert(minishell->input, c, minishell->cursor);
			minishell->cursor++;
			prompt(minishell, "\r");
		}
		ft_fflush(stdout);
	}
}
