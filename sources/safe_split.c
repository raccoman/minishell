#include "minishell.h"

void	jump_quote(char *input, int *i, char type)
{
	(*i)++;
	if (type == '\'')
	{
		while (input[*i] != '\'')
			(*i)++;
	}
	else if (type == '\"')
	{
		while (1)
		{
			if (input[*i] == '\"' && input[*i - 1] != '\\')
				break ;
			 (*i)++;
		}
	}
	(*i)++;
}

char	**split_token(int i, int start, char *input, char **splitted)
{
	char	*token;

	if (!input[i] && (i == start || ft_onlythischar(&input[start], ' ')))
	{
		if (!splitted)
			splitted = ft_append_element(splitted, 0);
		return (splitted);
	}
	if (start == i)
	{
		print_error("syntax error", "expected command");
		ft_free2D((void **)splitted);
		splitted = NULL;
		return (ft_append_element(splitted, 0));
	}
	token = malloc((i - start + 1));
	ft_strlcpy(token, input + start, i - start + 1);
	if (ft_onlythischar(token, ' '))
	{
		print_error("syntax error", "expected command");
		ft_free2D((void **)splitted);
		splitted = NULL;
		return (ft_append_element(splitted, 0));
	}
	return (ft_append_element(splitted, token));
}

char	**safe_split(char *input, char del)
{
	char	**splitted;
	int		i;
	int		start;
	char	*token;

	splitted = NULL;
	i = 0;
	start = 0;
	while (1)
	{
		if (input[i] == '\\')
			i += 2;
		if (input[i] == '\'' || input[i] == '\"')
			jump_quote(input, &i, input[i]);
		if (input[i] == del || !input[i])
		{
			splitted = split_token(i, start, input, splitted);
			if (!(*splitted) || !input[i])
				break ;
			start = ++i;
		}
		else
			i++;
	}
	return (splitted);
}
