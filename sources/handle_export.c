#include "minishell.h"

void	single_export(t_minishell *minishell, char *export)
{
	t_list	*env;

	if (is_assign(export))
		single_assign(minishell, ft_strdup(export));
	env = find_env(minishell->main_env, export);
	if (env)
		return ;
	env = find_env(minishell->session_env, export);
	if (env)
	{
		ft_lstadd_back(&minishell->main_env, ft_lstnew(ft_strdup(env->data)));
		ft_lstrmv_if(&minishell->session_env, export, &cmd_cmp, &free);
	}
}

char	*get_name(const char *env)
{
	int	i;
	char	*name;

	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	name = malloc(sizeof(char) * (i + 1));
	i = 0;
	while (env[i] && env[i] != '=')
	{
		name[i] = env[i];
		i++;
	}
	name[i] = 0;
	return (name);
}
char	*get_value(const char *env)
{
	int	offset;
	int	i;
	char	*value;

	offset = 0;
	while (env[offset] && env[offset] != '=')
		offset++;
	offset++;
	i = 0;
	while (env[i + offset])
		i++;
	value = malloc(sizeof(char) * (i + 1));
	i = 0;
	while (env[i + offset])
	{
		value[i] = env[i + offset];
		i++;
	}
	value[i] = 0;
	return (value);
}

void	no_args(t_minishell *minishell)
{
	t_list	*env;
	char	*current;
	char	*name;
	char	*value;

	env = minishell->main_env;
	while (env)
	{
		current = (char *)env->data;
		name = get_name(current);
		value = get_value(current);
		printf("declare -x %s=\"%s\"\n", name, value);
		free(name);
		free(value);
		env = env->next;
	}
}

void	handle_export(t_minishell *minishell, t_simple_cmd *curr)
{
	int 	i;
	char 	**args;

	args = &(curr->arguments[1]);
	if (!args[0])
	{
		no_args(minishell);
		return ;
	}
	i = 0;
	while (args[i])
		single_export(minishell, args[i++]);
}