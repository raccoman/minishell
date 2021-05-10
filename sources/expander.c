#include "minishell.h"

void	expander(t_minishell *minishell, t_simple_cmd *curr)
{
	int		i;
	char	*env_value;
	char	*env_name;

	i = -1;
	while (curr->arguments[++i])
	{
		if (*curr->arguments[i] == '$' && curr->arguments[i][1])
		{
			env_name = ft_strdup(curr->arguments[i] + 1);
			free(curr->arguments[i]);
			env_value = get_env_value(minishell, env_name);
			if (!env_value)
				curr->arguments[i] = ft_strdup("");
			else
				curr->arguments[i] = ft_strdup(env_value);
		}
	}
}