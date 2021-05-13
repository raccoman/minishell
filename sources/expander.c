#include "minishell.h"

void	delete_arguemnts(t_simple_cmd *curr, int deleted)
{
	int	i;

	i = 0;
	while (curr->arguments[i++])
	{
		
	}
}

void	expander(t_minishell *minishell, t_simple_cmd *curr)
{
	int		i;
	char	*env_value;
	char	*env_name;
	int		deleted;

	deleted = 0;
	while (curr)
	{
		i = -1;
		while (curr->arguments[++i])
		{
			if (*curr->arguments[i] == '$' && curr->arguments[i][1])
			{
				env_name = ft_strdup(curr->arguments[i] + 1);
				free(curr->arguments[i]);
				env_value = get_env_value(minishell, env_name);
				if (!env_value)
					curr->arguments[i] = 0;
				else
					curr->arguments[i] = ft_strdup(env_value);
			}
		}
		curr = curr->next;
	}
	if (deleted)
		delete_arguemnts(curr, deleted);
}