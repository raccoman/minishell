/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_export.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgiordanraccoman <marvin@42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 13:14:22 by mgiordan          #+#    #+#             */
/*   Updated: 2021/05/24 13:14:29 by mgiordan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	else if (!find_env(minishell->exported, export))
		ft_lstadd_back(&minishell->exported, ft_lstnew(ft_strdup(export)));
}

void	sort_matrix(char **matrix, int len)
{
	int		unordered;
	char	*tmp;
	int		i;
	char	*name1;
	char	*name2;

	unordered = 0;
	i = -1;
	while (++i < len - 1)
	{
		name1 = env_name(matrix[i]);
		name2 = env_name(matrix[i + 1]);
		if (ft_strcmp(name1, name2) > 0)
		{
			unordered = 1;
			tmp = matrix[i];
			matrix[i] = matrix[i + 1];
			matrix[i + 1] = tmp;
		}
		free(name1);
		free(name2);
	}
	if (unordered)
		return (sort_matrix(matrix, len - 1));
}

void	print_declare(char **envs)
{
	int		i;
	char	**splitted;

	i = -1;
	while (envs[++i])
	{
		if (!ft_contains(envs[i], '='))
		{
			printf("declare -x %s\n", envs[i]);
			continue ;
		}
		splitted = ft_split(envs[i], '=');
		if (!splitted[1])
			printf("declare -x %s=\"\"\n", splitted[0]);
		else
			printf("declare -x %s=\"%s\"\n", splitted[0], splitted[1]);
		ft_free2D((void **)splitted);
	}
}

void	no_args(t_minishell *minishell)
{
	char	**envs;
	int		i;
	t_list	*tmp;

	envs = lst_to_matrix(minishell->main_env);
	tmp = minishell->exported;
	while (tmp)
	{
		envs = ft_append_element(envs, ft_strdup((char *)tmp->data));
		tmp = tmp->next;
	}
	i = 0;
	while (envs[i])
		i++;
	sort_matrix(envs, i);
	print_declare(envs);
	ft_free2D((void **)envs);
}

void	handle_export(t_minishell *minishell, t_simple_cmd *curr)
{
	int		i;
	char	**args;

	args = &(curr->arguments[1]);
	if (!check_option("export: ", *args))
		return ;
	if (!args[0])
		return (no_args(minishell));
	i = 0;
	while (args[i])
		single_export(minishell, args[i++]);
}
