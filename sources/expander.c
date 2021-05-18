#include "minishell.h"

void	delete_arguments(t_simple_cmd *curr)
{
	int		i;
	int		j;
	char	**new_arg;

	i = -1;
	j = 0;
	while (curr->arguments[++i])
	{
		if (*(curr->arguments[i]))
			j++;
	}
	new_arg = malloc((j + 1) * sizeof(char *));
	i = -1;
	j = 0;
	while (curr->arguments[++i])
	{
		if (*(curr->arguments[i]))
			new_arg[j++] = curr->arguments[i];
		else
			free(curr->arguments[i]);
	}
	new_arg[j] = 0;
	free(curr->arguments);
	curr->arguments = new_arg;
}

char	*expand_var(t_minishell *minishell, char *token, int *i)
{
	char	*var_name;
	char	*var_value;

	(*i)++;
	var_name = NULL;
	var_name = ft_append(var_name, 0);
	while (token[*i] && !ft_contains(" \'\"\\", token[*i]))
		var_name = ft_append(var_name, token[(*i)++]);
	var_value = get_env_value(minishell, var_name);
	free(var_name);
	if (var_value)
		return (ft_strdup(var_value));
	return(ft_strdup(""));
}

char	*expand_quote(char *token, int *i)
{
	char	*quote;

	(*i)++;
	quote = NULL;
	quote = ft_append(quote, 0);
	while (token[*i] != '\'')
		quote = ft_append(quote, token[(*i)++]);
	(*i)++;
	return (quote);
}

char	*expand_dquote(t_minishell *minishell, char *token, int *i)
{
	char	*dquote;
	char	*join;
	char	*safe;

	(*i)++;
	dquote = NULL;
	dquote = ft_append(dquote, 0);
	while (token[*i] != '\"')
	{
		if (token[*i] == '$' && !ft_contains(" \'\"", token[*i + 1]))
		{
			join = expand_var(minishell, token, i);
			safe = dquote;
			dquote = ft_strjoin(dquote, join);
			free(safe);
			free(join);
			continue ;
		}
		if (token[*i] == '\\' && ft_contains("$\"", token[*i + 1]))
			(*i)++;
		dquote = ft_append(dquote, token[(*i)++]);
	}
	(*i)++;
	return (dquote);
}

char	*expand_token(t_minishell *minishell, char *token)
{
	int		i;
	char	*result;
	char	*safe;
	char	*join;

	result = malloc(1);
	*result = 0;
	i = 0;
	while (token[i])
	{
		join = NULL;
		if (token[i] == '$' && token[i + 1] && !ft_contains(" \'\"", token[i + 1]))
			join = expand_var(minishell, token, &i);
		else if (token[i] == '\'')
			join = expand_quote(token, &i);
		else if (token[i] == '\"')
			join = expand_dquote(minishell, token, &i);
		if (join)
		{
			safe = result;
			result = ft_strjoin(result, join);
			free(safe);
			free(join);
			continue ;
		}
		if (token[i] == '\\')
			i++;
		result = ft_append(result, token[i++]);
	}
	free(token);
	return (result);
}

void	expander(t_minishell *minishell, t_simple_cmd *curr)
{
	int	i;

	while (curr)
	{
		i = -1;
		while (curr->arguments[++i])
			curr->arguments[i] = expand_token(minishell, curr->arguments[i]);
		delete_arguments(curr);
		curr = curr->next;
	}
}