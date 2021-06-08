/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgiordanraccoman <marvin@42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 13:16:10 by mgiordan          #+#    #+#             */
/*   Updated: 2021/05/24 13:16:12 by mgiordan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_key	read_wrapper(t_minishell *minishell, char *c)
{
	t_key	key;

	ft_fflush(stdout);
	tcsetattr(0, TCSANOW, &minishell->our_cfg);
	read(0, c, 1);
	key = get_key(*c);
	tcsetattr(0, TCSANOW, &minishell->sys_cfg);
	return (key);
}

void	update_input(t_minishell *minishell, char c)
{
	int	tmp;
	int	length;

	minishell->input = ft_insert(minishell->input, \
		c, minishell->cursor);
	update_history(minishell->history, minishell->input);
	minishell->cursor++;
	tmp = minishell->cursor;
	if (tmp != ft_strlen(minishell->input))
	{
		handle_key(minishell, KEY_END);
		minishell->last_len++;
	}
	prompt(minishell, "\r");
	minishell->cursor = tmp;
	length = ft_strlen(minishell->input);
	while (minishell->cursor < length--)
		printf("\033[1D");
	ft_fflush(stdout);
}

void	get_input(t_minishell *minishell)
{
	char	c;
	t_key	key;

	minishell->pid = -1;
	while (1)
	{
		key = read_wrapper(minishell, &c);
		if (key == KEY_ENTER)
			break ;
		else if (key != KEY_ALPHANUMERIC)
			handle_key(minishell, key);
		else
			update_input(minishell, c);
		ft_fflush(stdout);
	}
}
