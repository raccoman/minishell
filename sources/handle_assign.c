/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_assign.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgiordanraccomna <marvin@42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 13:13:24 by mgiordan          #+#    #+#             */
/*   Updated: 2021/05/24 13:13:25 by mgiordan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	update_args(t_simple_cmd *curr)
{
	int		arg_num;
	int		i;
	int		j;
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
}

void	redirect_cmd(t_minishell *minishell, t_simple_cmd *curr)
{
	update_args(curr);
	if (builtins(curr->arguments[0], curr, minishell))
		return ;
	minishell->pid = fork();
	if (!minishell->pid)
	{
		execute_non_builtin(curr, minishell);
		print_error(curr->arguments[0], strerror(errno));
		exit(1);
	}
	waitpid(minishell->pid, NULL, 0);
	minishell->pid = -1;
}

void	single_assign(t_minishell *minishell, char *assign)
{
	char	*var_name;
	t_list	*env;

	var_name = env_name(assign);
	env = find_env(minishell->main_env, var_name);
	if (env)
	{
		free(env->data);
		env->data = assign;
	}
	env = find_env(minishell->exported, var_name);
	if (env)
	{
		ft_lstadd_back(&minishell->main_env, ft_lstnew(assign));
		ft_lstrmv_if(&minishell->exported, var_name, &cmd_cmp, &free);
	}
	env = find_env(minishell->session_env, var_name);
	if (env)
	{
		free(env->data);
		env->data = assign;
	}
	else if (!find_env(minishell->main_env, var_name))
		ft_lstadd_back(&minishell->session_env, ft_lstnew(assign));
	free(var_name);
}

void	handle_assign(t_minishell *minishell, t_simple_cmd *curr)
{
	int	i;

	if (!check_assigns(curr->arguments))
	{
		redirect_cmd(minishell, curr);
		return ;
	}
	i = -1;
	while (curr->arguments[++i])
		single_assign(minishell, ft_strdup(curr->arguments[i]));
}
