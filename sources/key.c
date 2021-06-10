/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgiordanraccoman <marvin@42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 13:16:23 by mgiordan          #+#    #+#             */
/*   Updated: 2021/05/24 13:16:24 by mgiordan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_key	get_key_3(void)
{
	char	c;

	read(0, &c, 1);
	if (c == '\x3b')
	{
		read(0, &c, 1);
		if (c == '\x32')
		{
			read(0, &c, 1);
			if (c == '\x41')
				return (KEY_SHIFT_UP);
			if (c == '\x42')
				return (KEY_SHIFT_DOWN);
			if (c == '\x44')
				return (KEY_SHIFT_LEFT);
			if (c == '\x43')
				return (KEY_SHIFT_RIGHT);
		}
	}
	return (KEY_UNKNOWN);
}

t_key	get_key_2(char c)
{
	if (c == '\x5b')
	{
		read(0, &c, 1);
		if (c == '\x41')
			return (KEY_UP);
		if (c == '\x42')
			return (KEY_DOWN);
		if (c == '\x43')
			return (KEY_RIGHT);
		if (c == '\x44')
			return (KEY_LEFT);
		if (c == '\x48')
			return (KEY_HOME);
		if (c == '\x46')
			return (KEY_END);
		if (c == '\x31')
			return (get_key_3());
	}
	return (KEY_UNKNOWN);
}

t_key	get_key(char c)
{
	if (c >= 32 && c <= 126)
		return (KEY_ALPHANUMERIC);
	if (c == '\x10')
		return (KEY_CTRL_P);
	if (c == '\x18')
		return (KEY_CTRL_X);
	if (c == '\x15')
		return (KEY_CTRL_U);
	if (c == '\x04')
		return (KEY_EOF);
	if (c == '\x09')
		return (KEY_TAB);
	if (c == '\x0a')
		return (KEY_ENTER);
	if (c == '\x7f')
		return (KEY_CANCEL);
	if (c == '\x1b')
	{
		read(0, &c, 1);
		return (get_key_2(c));
	}
	return (KEY_UNKNOWN);
}

void	handle_key(t_minishell *sh, t_key key)
{
	if (key == KEY_CANCEL)
	{
		if (!sh->cursor)
			printf("\a");
		else
		{
			sh->cursor--;
			sh->input = ft_remove_at(sh->input, sh->cursor);
			update_history(sh->history, sh->input);
			prompt(sh, "\r");
		}
	}
	if (key == KEY_EOF || key == KEY_HOME
		|| key == KEY_END)
		eof_home_end(sh, key);
	if (key == KEY_CTRL_X || key == KEY_CTRL_P
		|| key == KEY_CTRL_U)
		copy_paste(sh, key);
	if (key == KEY_SHIFT_LEFT || key == KEY_LEFT
		|| key == KEY_SHIFT_RIGHT || key == KEY_RIGHT)
		left_right(sh, key);
	if (key == KEY_UP || key == KEY_SHIFT_UP
		|| key == KEY_DOWN || key == KEY_SHIFT_DOWN)
		up_down(sh, key);
}

void	handle_enter(t_minishell *minishell)
{
	if (minishell->input
		&& minishell->cursor != ft_strlen(g_minishell->input))
		handle_key(g_minishell, KEY_END);
	printf(CC_RESET "\n");
	if (!first_check(minishell, minishell->input))
		return ;
	if (minishell->input)
	{
		add_history(minishell, minishell->input);
		minishell->input = parse_wildcards(minishell->input);
		parse_priorities(minishell);
		minishell->semicols = safe_split(minishell->input, ';');
		free(minishell->input);
		execute_semicols(minishell, minishell->o_input);
		free(minishell->o_input);
		minishell->o_input = NULL;
		ft_free2D((void **)minishell->semicols);
		minishell->semicols = NULL;
		minishell->input = NULL;
	}
	minishell->cursor = 0;
	adjust_prompt(minishell);
	minishell->last_len = PROMPT_LEN;
	prompt(minishell, "");
}
