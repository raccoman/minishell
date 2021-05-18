#include "minishell.h"

int	calc_token_len(char *str)
{
	int	count;

	count = 0;
	while (str[count] && !ft_contains(" <>", str[count]))
		count++;
	return(count);
}

void	parse_quote(char **input, char *token, int *i)
{
	char	*str;

	str = *input;
	token[(*i)++] = *str++;
	while (*str != '\'')
		token[(*i)++] = *str++;
	(*input) = str;
}

void	parse_dquote(char **input, char *token, int *i)
{
	char	*str;

	str = *input;
	token[(*i)++] = *str++;
	while (1)
	{
		if (*str == '\"')
			break ;
		if (*str == '\\' && str[1] == '\"')
			token[(*i)++] = *str++;
		else if (*str == '\\' && ft_contains("\';|\\", str[1]))
			str++;
		token[(*i)++] = *str++;
	}
	(*input) = str;
}

char	*get_next_token(char **input)
{
	int		i;
	char	*token;
	char	*result;

	token = malloc(ft_strlen(*input) + 1);
	i = 0;
	while (**input && !ft_contains(" <>", **input))
	{
		if (**input == '\'')
			parse_quote(input, token, &i);
		if (**input == '\"')
			parse_dquote(input, token, &i);
		if (**input == '\\')
		{
			token[i++] = **input;
			(*input)++;
		}
		token[i++] = **input;
		(*input)++;
	}
	token[i] = 0;
	result = ft_strdup(token);
	free(token);
	return (result);
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
	if (command->here_doc)
	{
		if (command->infile)
			free(command->infile);
		command->infile = path;
		return (1);
	}
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
		fd = open(path, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
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
		if (!*splitted)
			break ;
		buff = get_next_token(&splitted);
		rslt->arguments = ft_append_element(rslt->arguments, buff);
		while (*splitted == ' ')
			splitted++;
		if (*splitted == '<')
		{
			command->here_doc = 0;
			if (*(splitted + 1) == '<')
			{
				splitted++;
				command->here_doc = 1;
			}
			file_ret = handle_infile(&splitted, command);
		}
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