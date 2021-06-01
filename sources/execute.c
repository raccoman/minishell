/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgiordanraccoman <marvin@42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 13:12:54 by mgiordan          #+#    #+#             */
/*   Updated: 2021/05/24 13:12:56 by mgiordan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_path(t_simple_cmd *cmd, char **env_matrix)
{
	int		len;
	int		i;
	int		j;
	char	*path;

	path = *cmd->arguments;
	len = ft_strlen(path);
	i = len;
	while (i && path[i - 1] != '\\')
		i--;
	*cmd->arguments = malloc(len - i + 1);
	j = 0;
	while (path[i])
		(*cmd->arguments)[j++] = path[i++];
	(*cmd->arguments)[j] = 0;
	execve(path, cmd->arguments, env_matrix);
	ft_free2D((void **)env_matrix);
}

void	execute_non_builtin(t_simple_cmd *cmd, t_minishell *minishell)
{
	char	**paths;
	char	**env_matrix;
	char	*try_path;
	char	*safe;
	int		i;

	env_matrix = lst_to_matrix(minishell->main_env);
	if (is_path(*cmd->arguments) || !find_env(minishell->main_env, "PATH"))
		return (execute_path(cmd, env_matrix));
	paths = ft_split(get_env_value(minishell, "PATH"), ':');
	i = -1;
	while (paths[++i])
	{
		try_path = ft_strjoin(paths[i], "/");
		safe = try_path;
		try_path = ft_strjoin(try_path, *cmd->arguments);
		free(safe);
		execve(try_path, cmd->arguments, env_matrix);
		if (errno != ENOENT)
			break ;
	}
	ft_free2D((void **)paths);
	ft_free2D((void **)env_matrix);
}

int	execute_pipe(t_minishell *minishell, t_simple_cmd *curr)
{
	int	status;

	minishell->pid = fork();
	if (!minishell->pid)
	{
		if (!builtins(curr->arguments[0], curr, minishell))
		{
			execute_non_builtin(curr, minishell);
			print_error(curr->arguments[0], strerror(errno));
		}
		exit(errno);
	}
	waitpid(minishell->pid, &status, 0);
	return (status);
}

void	execute_pipeline(t_minishell *minishell,
	t_command *command, int *tmp_stds)
{
	t_simple_cmd	*curr;
	int				fdin;
	int				fdpipe[2];
	int				status;

	curr = command->s_commands;
	fdin = redirect_infile(command->infile, *tmp_stds, command->here_doc, 0);
	while (curr)
	{
		dup2(fdin, 0);
		close(fdin);
		if (!curr->next)
			redirect_outfile(command->outfile, tmp_stds[1], command->append);
		else
		{
			pipe(fdpipe);
			fdin = fdpipe[0];
			dup2(fdpipe[1], 1);
			close(fdpipe[1]);
		}
		status = execute_pipe(minishell, curr);
		curr = curr->next;
	}
	set_statusenv(minishell, status / 256);
	minishell->pid = -1;
}
