/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keys.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgiordanraccoman <marvin@42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 13:14:36 by mgiordan          #+#    #+#             */
/*   Updated: 2021/05/24 13:14:38 by mgiordan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	shift_cursor_left(t_minishell *sh)
{
	sh->cursor--;
	printf("\033[1D");
}

void	shift_cursor_right(t_minishell *sh)
{
	struct winsize	size;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
	if (!((sh->cursor + PROMPT_LEN) % size.ws_col))
		printf("\033[1B\r");
	else
		printf("\033[1C");
	sh->cursor++;
}

int	check_cursor(t_minishell *sh, t_key key, int *i)
{
	if (key == KEY_SHIFT_LEFT || key == KEY_LEFT)
		*i = 0;
	else
		*i = ft_strlen(sh->input);
	if (sh->cursor == *i)
	{
		printf("\a");
		return (0);
	}
	return (1);
}

void	eof_home_end(t_minishell *sh, t_key key)
{
	int	i;

	i = 0;
	if (key == KEY_EOF && sh->input && *sh->input)
		i = -1;
	else if (key == KEY_END)
		i = ft_strlen(sh->input);
	if ((key == KEY_EOF && i == -1)
		|| (key != KEY_EOF && sh->cursor == i))
	{
		printf("\a");
		return ;
	}
	while (key == KEY_HOME && sh->cursor)
		shift_cursor_left(sh);
	while (key == KEY_END && sh->cursor < i)
		shift_cursor_right(sh);
	if (key == KEY_EOF)
	{
		printf("exit\n");
		handle_exit(sh, NULL);
	}
}

void	left_right(t_minishell *sh, t_key key)
{
	int	i;

	if (!check_cursor(sh, key, &i))
		return ;
	if (key == KEY_SHIFT_LEFT)
	{
		shift_cursor_left(sh);
		while (sh->cursor && sh->input[sh->cursor] == ' ')
			shift_cursor_left(sh);
		while (sh->cursor && sh->input[sh->cursor - 1] != ' ')
			shift_cursor_left(sh);
	}
	if (key == KEY_LEFT)
		shift_cursor_left(sh);
	if (key == KEY_SHIFT_RIGHT)
	{
		while (sh->cursor < i && sh->input[sh->cursor] != ' ')
			shift_cursor_right(sh);
		while (sh->cursor < i && sh->input[sh->cursor] == ' ')
			shift_cursor_right(sh);
	}
	if (key == KEY_RIGHT)
		shift_cursor_right(sh);
}
