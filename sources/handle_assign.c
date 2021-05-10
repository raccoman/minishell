#include "minishell.h"

char	*env_name(const char *str)
{
	char	*rslt;
	int		i;

	i = 0;
	while (str[i] != '=')
		i++;
	rslt = malloc(i + 1);
	i = 0;
	while (*str != '=')
		rslt[i++] = *str++;
	rslt[i] = 0;
	return (rslt);
}

int	check_assigns(char **assigns)
{
	int	i;

	i = 1;
	while (assigns[i])
	{
		if (!is_assign(assigns[i++]))
			return (0);
	}
	return (1);
}

void	redirect_cmd(t_minishell *minishell, t_simple_cmd *curr)
{
	int		i;
	int		j;
	int		arg_num;
	char	**new_arguments;
 
	arg_num = 0;
	while (curr->arguments[arg_num])
		arg_num++;
	i = 0;
	while (is_assign(curr->arguments[i]))
		i++;
	new_arguments = malloc((arg_num - i + 1) * sizeof(char *));
	j = 0;
	while (curr->arguments[i])
		new_arguments[j++] = ft_strdup(curr->arguments[i++]);
	new_arguments[j] = 0;
	ft_free2D((void **)curr->arguments);
	curr->arguments = new_arguments;
	dispatcher(curr->arguments[0], curr, minishell);
}

void	handle_assign(t_minishell *minishell, t_simple_cmd *curr)
{
	t_list	*env;
	char	*var_name;
	char	*assign;

	if (!check_assigns(curr->arguments))
	{
		redirect_cmd(minishell, curr);
		return ;
	}
	assign = ft_strdup(*(curr->arguments));
	var_name = env_name(assign);
	env = find_env(minishell->main_env, var_name);
	if (env)
	{
		free(env->data);
		env->data = assign;
		return ;
	}
	env = find_env(minishell->session_env, var_name);
	if (env)
	{
		free(env->data);
		env->data = assign;
	}
	else
		ft_lstadd_back(&minishell->session_env, ft_lstnew(assign));
}