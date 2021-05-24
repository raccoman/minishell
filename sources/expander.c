/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgiordanraccoman <marvin@42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 13:13:16 by mgiordan          #+#    #+#             */
/*   Updated: 2021/05/24 13:13:17 by mgiordan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int	is_expandable(t_minishell *minishell, char *token, char **result, int *i)
{
	char	*expanded;
	char	*safe;

	expanded = NULL;
	if (token[*i] == '$' && token[*i + 1]
		&& !ft_contains(" \'\"", token[*i + 1]))
		expanded = expand_var(minishell, token, i);
	else if (token[*i] == '\'')
		expanded = expand_quote(token, i);
	else if (token[*i] == '\"')
		expanded = expand_dquote(minishell, token, i);
	if (expanded)
	{
		safe = *result;
		*result = ft_strjoin(*result, expanded);
		free(safe);
		free(expanded);
		return (1);
	}
	return (0);
}

char	*expand_token(t_minishell *minishell, char *token)
{
	int		i;
	char	*result;

	result = malloc(1);
	*result = 0;
	i = 0;
	while (token[i])
	{
		if (is_expandable(minishell, token, &result, &i))
			continue ;
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
