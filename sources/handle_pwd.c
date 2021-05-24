/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pwd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgiordanraccoman <marvin@42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 13:14:45 by mgiordan          #+#    #+#             */
/*   Updated: 2021/05/24 13:14:46 by mgiordan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_pwd(t_simple_cmd *curr)
{
	char	cwd[PATH_MAX];
	char	**args;

	args = &(curr->arguments[1]);
	if (!check_option("pwd: ", *args))
		return ;
	getcwd(cwd, sizeof(cwd));
	printf("%s\n", cwd);
}
