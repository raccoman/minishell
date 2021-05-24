/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgiordanraccoman <marvin@42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 13:16:46 by mgiordan          #+#    #+#             */
/*   Updated: 2021/05/24 13:16:47 by mgiordan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_dquote(char **input, char *token, int *i)
{
	char	*str;

	str = *input;
	token[(*i)++] = *str++;
	while (1)
	{
		if (*str == '\"')
			break ;
		if (*str == '\\' && str[1] == '\"')
			token[(*i)++] = *str++;
		else if (*str == '\\' && ft_contains("\';|\\", str[1]))
			str++;
		token[(*i)++] = *str++;
	}
	(*input) = str;
}

void	parse_quote(char **input, char *token, int *i)
{
	char	*str;

	str = *input;
	token[(*i)++] = *str++;
	while (*str != '\'')
		token[(*i)++] = *str++;
	(*input) = str;
}

char	*get_next_token(char **input)
{
	int		i;
	char	*token;
	char	*result;

	token = malloc(ft_strlen(*input) + 1);
	i = 0;
	while (**input && !ft_contains(" <>", **input))
	{
		if (**input == '\'')
			parse_quote(input, token, &i);
		if (**input == '\"')
			parse_dquote(input, token, &i);
		if (**input == '\\')
		{
			token[i++] = **input;
			(*input)++;
		}
		token[i++] = **input;
		(*input)++;
	}
	token[i] = 0;
	result = ft_strdup(token);
	free(token);
	return (result);
}

int	check_file(t_minishell *minishell, char **input, char *error_msg)
{
	(*input)++;
	while (**input == ' ')
		(*input)++;
	if (!(**input))
	{
		print_error("syntax error", error_msg);
		single_assign(minishell, ft_strdup("?=258"));
		return (0);
	}
	return (1);
}
