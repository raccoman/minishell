#include "minishell.h"

void	delete_arguments(t_simple_cmd *curr)
{
	int		i;
	int		j;
	char	**new_arg;

	i = -1;
	j = 0;
	while (curr->arguments[++i])
	{
		if (*(curr->arguments[i]))
			j++;
	}
	new_arg = malloc((j + 1) * sizeof(char *));
	i = -1;
	j = 0;
	while (curr->arguments[++i])
	{
		if (*(curr->arguments[i]))
			new_arg[j++] = curr->arguments[i];
		else
			free(curr->arguments[i]);
	}
	new_arg[j] = 0;
	free(curr->arguments);
	curr->arguments = new_arg;
}

void	expander(t_minishell *minishell, t_simple_cmd *curr)
{
	int		i;
	char	*env_value;
	char	*env_name;
	int		deleted;

	while (curr)
	{
		deleted = 0;
		i = -1;
		while (curr->arguments[++i])
		{
			if (*curr->arguments[i] == '$' && curr->arguments[i][1])
			{
				env_name = ft_strdup(curr->arguments[i] + 1);
				free(curr->arguments[i]);
				env_value = get_env_value(minishell, env_name);
				if (!env_value)
				{
					deleted++;
					curr->arguments[i] = ft_strdup("");
				}
				else
					curr->arguments[i] = ft_strdup(env_value);
			}
		}
		if (deleted)
			delete_arguments(curr);
		curr = curr->next;
	}
}