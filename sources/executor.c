#include "minishell.h"

void	clear_commands(t_command *command)
{
	int				i;
	t_simple_cmd	*tmp;
	t_simple_cmd	*list_copy;

	list_copy = command->s_commands;
	while (list_copy)
	{
		i = 0;
		// todo : liberare simple_cmd->path se lo usiamo
		while (list_copy->arguments[i])
			free(list_copy->arguments[i++]);
		free(list_copy->arguments);
		tmp = list_copy->next;
		free(list_copy);
		list_copy = tmp;
	}
	command->s_commands = NULL;
	if (command->infile)
	{
		free(command->infile);
		command->infile = NULL;
	}
	if (command->outfile)
	{
		free(command->outfile);
		command->outfile = NULL;
	}
	command->append = 0;
}

void	dispatcher(char *name, t_simple_cmd *curr, t_minishell *minishell)
{
	int	i;

	i = 0;
	if (!ft_strcmp(name, "exit") && (i = 1))
		handle_exit(minishell);
	if (!ft_strcmp(name, "pwd") && (i = 1))
		handle_pwd(curr);
	if (!ft_strcmp(name, "echo") && (i = 1))
		handle_echo(curr);
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

void    executor(t_minishell *minishell, t_command *command)
{
	t_simple_cmd	*curr;

	curr = command->s_commands;
	while (curr)
	{
		expander(minishell, curr);
		dispatcher(curr->arguments[0], curr, minishell);
		curr = curr->next;
	}
	clear_commands(command);  
}