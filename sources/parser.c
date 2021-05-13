#include "minishell.h"

char	*get_next_token(char **input)
{
	int		i;
	char	*token;

	token = malloc(calc_token_len(*input) + 1);
	i = 0;
	while (**input && !ft_contains(" <>", **input))
	{
		token[i++] = **input;
		(*input)++;
	}
	token[i] = 0;
	return (token);
}

int	handle_infile(char **input, t_command *command)
{
	char	*path;
	int		i;
	int		fd;

	(*input)++;
	while (**input == ' ')
		(*input)++;
	if (!(**input))
	{
		print_error("syntax error", "expected infile");
		single_assign(g_minishell, ft_strdup("?=258"));
		return (0);
	}
	path = get_next_token(input);
	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		errno = 0;
		print_error(path, "No such file or directory");
		errno = ENOENT;
		return (0);
	}
	else
	{
		if (command->infile)
			free(command->infile);
		command->infile = path;
	}
	close(fd);
	return (1);
}

int	handle_outfile(char **input, t_command *command)
{
	char	*path;
	int		i;
	int		fd;

	(*input)++;
	while (**input == ' ')
		(*input)++;
	if (!(**input))
	{
		print_error("syntax error", "expected outfile");
		single_assign(g_minishell, ft_strdup("?=258"));
		return (0);
	}
	path = get_next_token(input);
	if (command->append)
		fd = open(path, O_WRONLY | O_CREAT | O_APPEND, S_IRWXU);
	else
		fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
	if (command->outfile)
		free(command->outfile);
	command->outfile = path;
	close(fd);
	return (1);
}

t_simple_cmd	*create_scmd(t_command *command, char *splitted)
{
	t_simple_cmd	*rslt;
	int				i;
	char			*buff;
	int				file_ret;

	rslt = malloc(sizeof(t_simple_cmd));
	rslt->arguments = NULL;
	i = 0;
	file_ret = 1;
	while (*splitted)
	{
		while (*splitted == ' ')
			splitted++;
		buff = get_next_token(&splitted);
		add_argument(rslt, buff);
		while (*splitted == ' ')
			splitted++;
		if (*splitted == '<')
			file_ret = handle_infile(&splitted, command);
		if (*splitted == '>')
		{
			command->append = 0;
			if (*(splitted + 1) == '>')
			{
				splitted++;
				command->append = 1;
			}
			file_ret = handle_outfile(&splitted, command);
		}
		if (!file_ret)
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
	// non gestisco ancora ' " 
	// IMPORTANTE: do per scontato che libero la lista di comandi (s_commands) ogni volta
	char			**simple_cmds;
	int				i;
	t_simple_cmd	*tmp;

	simple_cmds = ft_split(minishell->input, '|');
	i = 0;
	while (simple_cmds[i])
	{
		tmp = create_scmd(minishell->command, simple_cmds[i++]); // questo riempie la struttura t_simple_cmd e nel caso aggiorna infile e outfile
		if (!tmp)
			return (clear_commands(minishell->command));
		add_command(minishell->command, tmp); // questo aggiunge il nuovo simple commands alla lista dentro command
	}
	ft_free2D((void **)simple_cmds);
}