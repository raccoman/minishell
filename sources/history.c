/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgiordanraccoman <marvin@42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 13:15:53 by mgiordan          #+#    #+#             */
/*   Updated: 2021/05/24 13:15:55 by mgiordan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_history	*get_last_history(t_history *history)
{
	while (history->next)
		history = history->next;
	return (history);
}

t_history	*get_first_history(t_history *history)
{
	while (history->prec)
		history = history->prec;
	return (history);
}

void	add_history(t_minishell *minishell, char *cmd_line)
{
	t_history	*tmp;
	t_history	*tmp_2;
	t_history	*last;

	tmp = malloc(sizeof(t_history));
	tmp->cmd_line = ft_strdup(cmd_line);
	tmp->safe = ft_strdup(cmd_line);
	last = get_last_history(minishell->history);
	tmp_2 = last->prec;
	last->prec = tmp;
	tmp->next = last;
	tmp->prec = tmp_2;
	if (tmp_2)
		tmp_2->next = tmp;
	free(minishell->history->cmd_line);
	minishell->history->cmd_line = ft_strdup(minishell->history->safe);
	free(last->cmd_line);
	last->cmd_line = ft_strdup("");
	minishell->history = last;
}

void	clear_history(t_history *history)
{
	t_history	*first;
	t_history	*tmp;

	first = get_first_history(history);
	while (first)
	{
		free(first->cmd_line);
		free(first->safe);
		tmp = first->next;
		free(first);
		first = tmp;
	}
}

void	update_history(t_history *history, char *new_line)
{
	free(history->cmd_line);
	history->cmd_line = ft_strdup(new_line);
}
