#include "minishell.h"

void	dispatcher(char *name, t_simple_cmd *curr, t_minishell *minishell)
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
	if (!i)
		printf(CC_RESET "%s:" CC_RED " command not found" CC_RESET "\n", name);
}

void	execute_single_cmd(t_minishell *minishell, t_command *command, int *tmp_stds)
{
	t_simple_cmd	*cmd;

	cmd = command->s_commands;
	redirect_infile(command->infile, *tmp_stds, 1);
	redirect_outfile(command->outfile, tmp_stds[1], command->append);
	dispatcher(cmd->arguments[0], cmd, minishell);
}

void	execute_pipeline(t_minishell *minishell, t_command *command, int *tmp_stds)
{
	t_simple_cmd	*curr;
	int				fdin;
	int				fdpipe[2];
	int				pid;

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
		pid = fork();
		if (!pid)
		{
			dispatcher(curr->arguments[0], curr, minishell);
			exit(0);
		}
		curr = curr->next;
	}
	waitpid(pid, NULL, 0);
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