/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_unset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgiordanraccoman <marvin@42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 13:14:54 by mgiordan          #+#    #+#             */
/*   Updated: 2021/05/24 13:14:56 by mgiordan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_unset(t_minishell *minishell, t_simple_cmd *curr)
{
	int		i;
	char	**args;

	args = &(curr->arguments[1]);
	if (!check_option("unset: ", *args))
		return ;
	i = 0;
	while (args[i])
	{
		ft_lstrmv_if(&minishell->main_env, args[i], &cmd_cmp, &free);
		ft_lstrmv_if(&minishell->session_env, args[i], &cmd_cmp, &free);
		ft_lstrmv_if(&minishell->exported, args[i], &cmd_cmp, &free);
		i++;
	}
}
