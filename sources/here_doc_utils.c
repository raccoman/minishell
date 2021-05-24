/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgiordanraccoman <marvin@42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 13:15:45 by mgiordan          #+#    #+#             */
/*   Updated: 2021/05/24 13:15:46 by mgiordan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reset_input(t_minishell *minishell)
{
	if (minishell->input)
		free(minishell->input);
	minishell->input = ft_strdup("");
	prompt(minishell, "");
	minishell->cursor = 0;
}

char	*update_buffer(t_minishell *minishell, char *buffer)
{
	char	*safe;

	if (!buffer)
		ft_append(buffer, 0);
	minishell->input = ft_append(minishell->input, '\n');
	safe = buffer;
	buffer = ft_strjoin(buffer, minishell->input);
	free(safe);
	reset_input(minishell);
	return (buffer);
}

int	handle_eof(t_minishell *minishell, t_key key)
{
	if (key != KEY_EOF)
		return (1);
	if (!minishell->input || !*minishell->input)
	{
		printf("\n");
		return (0);
	}
	printf("\a");
	return (1);
}
