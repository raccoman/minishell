#include "minishell.h"

void	execute_path(t_simple_cmd *cmd, t_minishell *minishell, char **env_matrix)
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

	env_matrix =  get_env_matrix(minishell->main_env);
	if (is_path(*cmd->arguments))
		return (execute_path(cmd, minishell, env_matrix));
	paths = ft_split(get_env_value(minishell, "PATH"), ':');
	i = -1;
	while (paths[++i])
	{
		try_path = ft_strjoin(paths[i], "/");
		safe = try_path;
		try_path = ft_strjoin(try_path, *cmd->arguments);
		free(safe);
		execve(try_path, cmd->arguments, env_matrix);
	}
	ft_free2D((void **)paths);
	ft_free2D((void **)env_matrix);
}

int	builtins(char *name, t_simple_cmd *curr, t_minishell *minishell)
{
	int	i;

	i = 0;
	if (!ft_strcmp(name, "exit") && (i = 1))
		handle_exit(minishell);
	if (!ft_strcmp(name, "pwd") && (i = 1))
		handle_pwd(curr);
	if (!ft_strcmp(name, "echo") && (i = 1))
		handle_echo(minishell, curr);
	if (!ft_strcmp(name, "env") && (i = 1))
		handle_env(minishell);
	if (!ft_strcmp(name, "export") && (i = 1))
		handle_export(minishell, curr);
	if (!ft_strcmp(name, "cd") && (i = 1))
		handle_cd(minishell, curr);
	if (!ft_strcmp(name, "unset") && (i = 1))
		handle_unset(minishell, curr);
	if (is_assign(name) && (i = 1))
		handle_assign(minishell, curr);
	return (i);
}

void	execute_single_cmd(t_minishell *minishell, t_command *command, int *tmp_stds)
{
	t_simple_cmd	*cmd;
	int				pid;

	cmd = command->s_commands;
	redirect_infile(command->infile, *tmp_stds, 1);
	redirect_outfile(command->outfile, tmp_stds[1], command->append);
	if (builtins(cmd->arguments[0], cmd, minishell))
		return ;
	pid = fork();
	if (!pid)
	{
		execute_non_builtin(cmd, minishell);
		print_error(CC_RESET "%s:" CC_RED " command not found" CC_RESET "\n", cmd->arguments[0]);
		exit(1);
	}
	waitpid(pid, NULL, 0);
}

void	execute_pipeline(t_minishell *minishell, t_command *command, int *tmp_stds)
{
	t_simple_cmd	*curr;
	int				fdin;
	int				fdpipe[2];

	curr = command->s_commands;
	fdin = redirect_infile(command->infile, *tmp_stds, 0);
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
		minishell->pid = fork();
		if (!minishell->pid)
		{
			if (!builtins(curr->arguments[0], curr, minishell))
			{
				execute_non_builtin(curr, minishell);
				print_error(CC_RESET "%s:" CC_RED " command not found" CC_RESET "\n", curr->arguments[0]);
			}
			exit(0);
		}
		curr = curr->next;
	}
	waitpid(minishell->pid, NULL, 0);
	minishell->pid = 0;
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