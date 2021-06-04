/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgiordanraccoman <marvin@42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 13:17:36 by mgiordan          #+#    #+#             */
/*   Updated: 2021/05/24 13:17:37 by mgiordan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

char	**expected_cmd(char **splitted, char del)
{
	char	*error_msg;

	error_msg = ft_strdup("expected command before '");
	error_msg = ft_append(error_msg, del);
	error_msg = ft_append(error_msg, '\'');
	print_error("syntax error", error_msg);
	free(error_msg);
	ft_free2D((void **)splitted);
	splitted = NULL;
	return (ft_append_element(splitted, 0));
}

char	**split_token(int *inds, char *input, char **splitted, char del)
{
	char	*token;

	if (!input[*inds] && (*inds == inds[1]
			|| ft_onlythischar(&input[inds[1]], ' ')) && del == ';')
	{
		if (!splitted)
			splitted = ft_append_element(splitted, 0);
		return (splitted);
	}
	if (inds[1] == *inds)
		return (expected_cmd(splitted, del));
	token = malloc((*inds - inds[1] + 1));
	ft_strlcpy(token, input + inds[1], *inds - inds[1] + 1);
	if (ft_onlythischar(token, ' '))
		return (expected_cmd(splitted, del));
	return (ft_append_element(splitted, token));
}

char	**safe_split(char *input, char del)
{
	char	**splitted;
	int		inds[2];

	splitted = NULL;
	*inds = 0;
	inds[1] = 0;
	while (1)
	{
		if (input[*inds] == '\\')
			*inds += 2;
		else if (input[*inds] == '\'' || input[*inds] == '\"')
			jump_quote(input, inds, input[*inds]);
		else if (input[*inds] == del || !input[*inds])
		{
			splitted = split_token(inds, input, splitted, del);
			if (!(*splitted) || !input[*inds])
				break ;
			inds[1] = ++(*inds);
		}
		else
			(*inds)++;
	}
	return (splitted);
}
