/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgiordanraccoman <marvin@42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 13:12:31 by mgiordan          #+#    #+#             */
/*   Updated: 2021/05/24 13:12:35 by mgiordan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_commands(t_command *command)
{
	t_simple_cmd	*tmp;
	t_simple_cmd	*list_copy;

	list_copy = command->s_commands;
	while (list_copy)
	{
		ft_free2D((void **)list_copy->arguments);
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
	command->here_doc = 0;
}

void	add_command(t_command *command, t_simple_cmd *s_cmd)
{
	t_simple_cmd	*list_copy;

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
