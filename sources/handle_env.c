/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgiordanraccoman <marvin@42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 13:13:47 by mgiordan          #+#    #+#             */
/*   Updated: 2021/05/24 13:13:48 by mgiordan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_env(t_minishell *minishell, t_simple_cmd *curr)
{
	t_list	*tmp;
	char	**args;
	char	*error_prefix;

	args = &(curr->arguments[1]);
	if (!check_option("env: ", *args))
		return ;
	if (*args)
	{
		error_prefix = ft_strjoin("env: ", *args);
		print_error(error_prefix, "No such file or directory");
		free(error_prefix);
		single_assign(minishell, ft_strdup("?=127"));
		return ;
	}
	tmp = minishell->main_env;
	while (tmp)
	{
		printf("%s\n", (char *)tmp->data);
		tmp = tmp->next;
	}
}
