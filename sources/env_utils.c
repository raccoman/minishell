#include "minishell.h"

char	*env_name(const char *env)
{
	int		i;
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

int	cmd_cmp(char *s1, char *s2)
{
	int	len;

	len = ft_strlen(s2);
	return (ft_strncmp(s1, s2, len));
}

t_list	*find_env(t_list *env, char *name)
{
	while (env)
	{
		if (!cmd_cmp(env->data, name))
			return (env);
		env = env->next;
	}
	return (NULL);
}

char	*get_env_value(t_minishell *minishell, char *name)
{
	t_list	*env;
	int		i;

	env = find_env(minishell->main_env, name);
	if (!env)
	{
		env = find_env(minishell->session_env, name);
		if (!env)
			return (NULL);
	}
	i = 0;
	while (((char *)env->data)[i] != '=')
		i++;
	return (((char *)env->data) + (i + 1));
}

char	**get_env_matrix(t_list *env)
{
	char	**result;
	int		i;

	result = malloc((ft_lstsize(env) + 1) * sizeof(char *));
	i = 0;
	while (env)
	{
		result[i++] = ft_strdup(env->data);
		env = env->next;
	}
	result[i] = 0;
	return (result);
}
