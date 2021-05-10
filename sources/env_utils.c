#include "minishell.h"

int	is_assign(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (i && str[i] == '=')
			return (1);
		i++;
	}
	return(0);
}

int	cmd_cmp(char *s1, char *s2)
{
	int	i;
	int	len;

	len = ft_strlen(s2);
	if (len <= 0)
		return (0);
	i = 0;
	while (i < len && s1[i] && s1[i] == s2[i])
		i++;
	if (i == len)
		return (0);
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
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
