/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgiordanraccoman <marvin@42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 13:13:01 by mgiordan          #+#    #+#             */
/*   Updated: 2021/05/24 13:13:03 by mgiordan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_builtin	is_builtin(char *name)
{
	if (!ft_strcmp(name, "echo"))
		return (BUILTIN_ECHO);
	if (!ft_strcmp(name, "exit"))
		return (BUILTIN_EXIT);
	if (!ft_strcmp(name, "pwd"))
		return (BUILTIN_PWD);
	if (!ft_strcmp(name, "env"))
		return (BUILTIN_ENV);
	if (!ft_strcmp(name, "export"))
		return (BUILTIN_EXPORT);
	if (!ft_strcmp(name, "cd"))
		return (BUILTIN_CD);
	if (!ft_strcmp(name, "unset"))
		return (BUILTIN_UNSET);
	if (is_assign(name))
		return (BUILTIN_ASSIGN);
	return (NONE);
}

int	builtins(char *name, t_simple_cmd *curr, t_minishell *minishell)
{
	t_builtin	which_builtin;

	which_builtin = is_builtin(name);
	if (which_builtin == NONE)
		return (0);
	errno = 0;
	if (which_builtin == BUILTIN_ECHO)
		handle_echo(minishell, curr);
	single_assign(minishell, ft_strdup("?=0"));
	if (which_builtin == BUILTIN_EXIT)
		handle_exit(minishell, curr);
	if (which_builtin == BUILTIN_PWD)
		handle_pwd(curr);
	if (which_builtin == BUILTIN_ENV)
		handle_env(minishell, curr);
	if (which_builtin == BUILTIN_EXPORT)
		handle_export(minishell, curr);
	if (which_builtin == BUILTIN_CD)
		handle_cd(minishell, curr);
	if (which_builtin == BUILTIN_UNSET)
		handle_unset(minishell, curr);
	if (which_builtin == BUILTIN_ASSIGN)
		handle_assign(minishell, curr);
	return (1);
}

void	set_statusenv(t_minishell *minishell, int code)
{
	char	*statustoa;

	statustoa = ft_itoa(code);
	if ((code) == 2)
		single_assign(minishell, ft_strdup("?=127"));
	else if ((code) == 13)
		single_assign(minishell, ft_strdup("?=126"));
	else
		single_assign(minishell, ft_strjoin("?=", statustoa));
	free(statustoa);
}

void	execute_single_cmd(t_minishell *minishell,
	t_command *command, int *tmp_stds)
{
	t_simple_cmd	*cmd;
	int				status;

	cmd = command->s_commands;
	if (!(*cmd->arguments))
		return ;
	redirect_infile(command->infile, *tmp_stds, command->here_doc, 1);
	redirect_outfile(command->outfile, tmp_stds[1], command->append);
	if (builtins(cmd->arguments[0], cmd, minishell))
		return ;
	minishell->pid = fork();
	if (!minishell->pid)
	{
		execute_non_builtin(cmd, minishell);
		print_error(cmd->arguments[0], strerror(errno));
		exit(errno);
	}
	waitpid(minishell->pid, &status, 0);
	set_statusenv(minishell, status /= 256);
	minishell->pid = -1;
}

void	executor(t_minishell *minishell, t_command *command)
{
	int	tmp_stds[2];

	if (!command->s_commands)
		return (clear_commands(command));
	expander(minishell, command->s_commands);
	tmp_stds[0] = dup(0);
	tmp_stds[1] = dup(1);
	if (!command->s_commands->next)
		execute_single_cmd(minishell, command, tmp_stds);
	else
		execute_pipeline(minishell, command, tmp_stds);
	restore_stds(tmp_stds);
	clear_commands(command);
}
