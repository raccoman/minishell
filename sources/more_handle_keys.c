/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_handle_keys.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgiordanraccoman <marvin@42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 13:16:36 by mgiordan          #+#    #+#             */
/*   Updated: 2021/05/24 13:16:38 by mgiordan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	adjust_prompt(t_minishell *minishell)
{
	static char	*old_promt;

	if (minishell->prompt)
	{
		if (!old_promt)
			old_promt = minishell->prompt;
		else
		{
			if (minishell->prompt == old_promt)
			{
				free(minishell->prompt);
				minishell->prompt = NULL;
				old_promt = NULL;
			}
			else
				old_promt = minishell->prompt;
		}
	}
}

int	check_par(char *string, int previous)
{
	int	lvl;

	lvl = 0;
	while (*string)
	{
		if (*string == '(')
			lvl++;
		if (*string == ')')
			lvl--;
		string++;
	}
	if (lvl)
		return (2);
	return (previous);
}

int	first_check(t_minishell *minishell, char *input)
{
	int	check;

	if (input)
	{
		check = check_quote(minishell->input);
		check = check_par(minishell->input, check);
		if (!check || check == -1 || check == 2)
		{
			add_history(minishell, minishell->input);
			free(minishell->input);
			minishell->input = NULL;
			if (!check)
				print_error("syntax error", "missing quote");
			else if (check == -1)
				print_error("syntax error", "escape at the end of line");
			else
				print_error("syntax error", "missing bracket");
		}
		else
			return (1);
	}
	reset_input(minishell);
	return (0);
}

void	up_down(t_minishell *sh, t_key key)
{
	t_history	*tmp;
	int			curs_tmp;

	if (key == KEY_UP || key == KEY_SHIFT_UP)
		tmp = sh->history->prec;
	else
		tmp = sh->history->next;
	if (!tmp)
	{
		printf("\a");
		return ;
	}
	curs_tmp = sh->cursor;
	if (curs_tmp != ft_strlen(sh->input))
		handle_key(sh, KEY_END);
	sh->cursor = curs_tmp;
	sh->history = tmp;
	if (sh->input)
		free(sh->input);
	sh->input = ft_strdup(sh->history->cmd_line);
	if (key == KEY_UP || key == KEY_DOWN)
		sh->cursor = ft_strlen(sh->input);
	else if (sh->cursor >= ft_strlen(sh->input))
		sh->cursor = ft_strlen(sh->input);
	prompt(sh, "\r");
}

void	copy_paste(t_minishell *sh, t_key key)
{
	int	i;

	if ((key == KEY_CTRL_U && !sh->clipboard)
		|| (key != KEY_CTRL_U && (!sh->input || !*sh->input)))
	{
		printf("\a");
		return ;
	}
	if (key == KEY_CTRL_X)
	{
		sh->clipboard = ft_strdup(sh->input + sh->cursor);
		sh->input[sh->cursor] = 0;
		update_history(sh->history, sh->input);
		prompt(sh, "\r");
	}
	if (key == KEY_CTRL_P)
	{
		i = -1;
		while (sh->clipboard[++i])
			sh->input = ft_insert(sh->input, sh->clipboard[i], sh->cursor++);
		update_history(sh->history, sh->input);
		prompt(sh, "\r");
	}
	if (key == KEY_CTRL_U)
		sh->clipboard = ft_strdup(sh->input + sh->cursor);
}
