/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgiordanraccoman <marvin@42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 13:17:14 by mgiordan          #+#    #+#             */
/*   Updated: 2021/05/24 13:17:15 by mgiordan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_here_doc(char *delim, int *fdpipe, char *buffer)
{
	char	c;
	t_key	key;

	reset_input(g_minishell);
	while (1)
	{
		key = read_wrapper(g_minishell, &c);
		if (!handle_eof(g_minishell, key))
			break ;
		if (key == KEY_ENTER)
		{
			printf("\n");
			if (!ft_strcmp(g_minishell->input, delim))
				break ;
			buffer = update_buffer(g_minishell, buffer);
		}
		else if (key != KEY_ALPHANUMERIC && key != KEY_EOF)
			handle_key(g_minishell, key);
		else if (key != KEY_EOF)
			update_input(g_minishell, c);
	}
	write(fdpipe[1], buffer, ft_strlen(buffer));
	free(buffer);
	exit(0);
}

int	redirect_infile(char *infile, int tmpin, int here_doc, int single)
{
	int	fds[2];

	if (here_doc)
	{
		pipe(fds);
		g_minishell->pid = fork();
		if (!g_minishell->pid)
			handle_here_doc(infile, fds, NULL);
		waitpid(g_minishell->pid, NULL, 0);
		g_minishell->pid = -1;
		close(fds[1]);
		printf(CC_RESET);
		ft_fflush(stdout);
	}
	else if (infile)
		*fds = open(infile, O_RDONLY);
	else
		*fds = dup(tmpin);
	if (single)
	{
		dup2(*fds, 0);
		close(*fds);
	}
	return (*fds);
}

void	redirect_outfile(char *outfile, int tmpout, int append)
{
	int	fdout;

	if (outfile)
	{
		if (append)
			fdout = open(outfile, O_WRONLY | O_APPEND);
		else
			fdout = open(outfile, O_WRONLY);
	}
	else
		fdout = dup(tmpout);
	dup2(fdout, 1);
	close(fdout);
}

void	restore_stds(int *tmp_stds)
{
	dup2(tmp_stds[0], 0);
	dup2(tmp_stds[1], 1);
	close(tmp_stds[0]);
	close(tmp_stds[1]);
}
