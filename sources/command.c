#include "minishell.h"

int	calc_token_len(char *str)
{
	int	count;

	count = 0;
	while (str[count] && !ft_contains(" <>", str[count]))
		count++;
	return(count);
}

void	add_argument(t_simple_cmd *s_cmd, char *new_arg)
{
	char	**new_arguments;
	int		i;

	i = 0;
	while(s_cmd->arguments && s_cmd->arguments[i])
		i++;
	new_arguments = malloc((i + 2) * sizeof(char *));
	i = 0;
	while(s_cmd->arguments && s_cmd->arguments[i])
	{
		new_arguments[i] = s_cmd->arguments[i];
		i++;
	}
	new_arguments[i++] = new_arg;
	new_arguments[i] = 0;
	if (s_cmd->arguments)
		free(s_cmd->arguments);
	s_cmd->arguments = new_arguments;
}

void	add_command(t_command *command, t_simple_cmd *s_cmd)
{
	int				i;
	t_simple_cmd	*list_copy;

	i = 0;
	if (!command->s_commands)
	{
		command->s_commands = s_cmd;
		return ;
	}
	list_copy = command->s_commands;
	while (list_copy->next)
		list_copy = list_copy->next;
	list_copy->next = s_cmd;
}