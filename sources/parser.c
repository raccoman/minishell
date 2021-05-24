/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgiordanraccoman <marvin@42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 13:16:54 by mgiordan          #+#    #+#             */
/*   Updated: 2021/05/24 13:16:56 by mgiordan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_infile(char **input, t_command *command)
{
	char	*path;
	int		fd;

	if (!check_file(g_minishell, input, "expected infile"))
		return (0);
	path = get_next_token(input);
	if (!command->here_doc)
	{
		fd = open(path, O_RDONLY);
		if (fd == -1)
		{
			errno = 0;
			print_error(path, "No such file or directory");
			errno = ENOENT;
			return (0);
		}
		close(fd);
	}
	if (command->infile)
		free(command->infile);
	command->infile = path;
	return (1);
}

int	handle_outfile(char **input, t_command *command)
{
	char	*path;
	int		fd;

	if (!check_file(g_minishell, input, "expected outfile"))
		return (0);
	path = get_next_token(input);
	if (command->append)
		fd = open(path, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (command->outfile)
		free(command->outfile);
	command->outfile = path;
	close(fd);
	return (1);
}

int	parse_files(t_command *command, char **splitted)
{
	int	file_ret;

	file_ret = 1;
	if (**splitted == '<')
	{
		command->here_doc = 0;
		if ((*splitted)[1] == '<')
		{
			(*splitted)++;
			command->here_doc = 1;
		}
		file_ret = handle_infile(splitted, command);
	}
	if (**splitted == '>')
	{
		command->append = 0;
		if ((*splitted)[1] == '>')
		{
			(*splitted)++;
			command->append = 1;
		}
		file_ret = handle_outfile(splitted, command);
	}
	return (file_ret);
}

t_simple_cmd	*create_scmd(t_command *command, char *splitted)
{
	t_simple_cmd	*rslt;
	char			*buff;

	rslt = malloc(sizeof(t_simple_cmd));
	rslt->arguments = NULL;
	while (*splitted)
	{
		while (*splitted == ' ')
			splitted++;
		if (!*splitted)
			break ;
		buff = get_next_token(&splitted);
		rslt->arguments = ft_append_element(rslt->arguments, buff);
		while (*splitted == ' ')
			splitted++;
		if (!parse_files(command, &splitted))
		{
			ft_free2D((void **)rslt->arguments);
			free(rslt);
			return (NULL);
		}
	}
	rslt->next = NULL;
	return (rslt);
}

void	parse_input(t_minishell *minishell)
{
	char			**simple_cmds;
	int				i;
	t_simple_cmd	*tmp;

	simple_cmds = safe_split(minishell->input, '|');
	i = 0;
	while (simple_cmds[i])
	{
		tmp = create_scmd(minishell->command, simple_cmds[i++]);
		if (!tmp)
			return (clear_commands(minishell->command));
		add_command(minishell->command, tmp);
	}
	ft_free2D((void **)simple_cmds);
}
