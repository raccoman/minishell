/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgiordanraccoman <marvin@42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 13:13:09 by mgiordan          #+#    #+#             */
/*   Updated: 2021/05/24 13:13:10 by mgiordan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_var(t_minishell *minishell, char *token, int *i)
{
	char	*var_name;
	char	*var_value;

	(*i)++;
	var_name = NULL;
	var_name = ft_append(var_name, 0);
	while (token[*i] && !ft_contains(" \'\"\\/", token[*i]))
		var_name = ft_append(var_name, token[(*i)++]);
	var_value = get_env_value(minishell, var_name);
	free(var_name);
	if (var_value)
		return (ft_strdup(var_value));
	return (ft_strdup(""));
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
