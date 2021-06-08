/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgiordanraccoman <marvin@42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 13:24:56 by mgiordan          #+#    #+#             */
/*   Updated: 2021/05/24 13:24:58 by mgiordan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_lines(t_minishell *minishell, int reset)
{
	struct winsize	size;
	float			to_remove;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
	to_remove = minishell->last_len / (float)size.ws_col;
	while (to_remove > 0)
	{
		printf("%c[2K", 27);
		if (reset)
			printf(CC_RESET "\r");
		if (to_remove > 1)
			printf("\033[1A");
		to_remove--;
	}
}

void	prompt(t_minishell *minishell, const char *prefix)
{
	int	length;

	if (minishell->pid != -1)
	{
		clear_lines(minishell, 1);
		printf(CC_CYN "> " CC_MAG "%s", minishell->input);
	}
	else
	{
		clear_lines(minishell, 0);
		printf(CC_RESET "%s", prefix);
		if (minishell->prompt)
			printf("%s", minishell->prompt);
		if (minishell->input)
			printf(CC_CYN "maxishell $> " CC_MAG "%s", minishell->input);
		else
			printf(CC_CYN "maxishell $> " CC_MAG);
	}
	length = ft_strlen(minishell->input);
	minishell->last_len = length + PROMPT_LEN + ft_strlen(minishell->prompt);
	while (minishell->cursor < length--)
		printf("\033[1D");
}

void	watermark(void)
{
	printf("%c[1;1H%c[2J", 27, 27);
	printf("\n" CC_CYN
		   "███╗   ███╗ █████╗ ██╗  ██╗██╗███\
████╗██╗  ██╗███████╗██╗     ██╗     \n"
		   "████╗ ████║██╔══██╗╚██╗██╔╝██║██╔═\
═══╝██║  ██║██╔════╝██║     ██║     \n"
		   "██╔████╔██║███████║ ╚███╔╝ ██║████\
███╗███████║█████╗  ██║     ██║     \n"
		   "██║╚██╔╝██║██╔══██║ ██╔██╗ ██║╚═══\
═██║██╔══██║██╔══╝  ██║     ██║     \n"
		   "██║ ╚═╝ ██║██║  ██║██╔╝ ██╗██║████\
███║██║  ██║███████╗███████╗███████╗\n"
		   "╚═╝     ╚═╝╚═╝  ╚═╝╚═╝  ╚═╝╚═╝╚═══\
═══╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝\n"
		   CC_WHT "Made by " CC_UGRN "raccoman"\
CC_WHT " and " CC_UGRN "mgiordan" CC_RESET "\n");
}

int	main(int argc, char *argv[], char *env[])
{
	g_minishell = malloc(sizeof(t_minishell));
	(void)argc;
	(void)argv;
	configure(g_minishell, env);
	watermark();
	printf(CC_CYN "maxishell $> " CC_MAG);
	while (1)
	{
		ft_fflush(stdout);
		get_input(g_minishell);
		handle_enter(g_minishell);
	}
	terminate(g_minishell);
	return (0);
}
