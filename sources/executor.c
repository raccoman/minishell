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
		while (list_copy->arguments[i])
			free(list_copy->arguments[i++]);
		free(list_copy->arguments);
		tmp = list_copy->next;
		free(list_copy);
		list_copy = list_copy->next;
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

void    executor(t_command *command)
{
		
	/*t_simple_cmd	*curr;
	int				i;

	curr = command->s_commands;
	printf("\n");
	while (curr)
	{
		i = 0;
		while (curr->arguments[i])
			printf("%s ", curr->arguments[i++]);
		printf("\n");
		curr = curr->next;
	}*/
	clear_commands(command);  
}