/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgiordanraccoman <marvin@42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 13:13:31 by mgiordan          #+#    #+#             */
/*   Updated: 2021/05/24 13:13:32 by mgiordan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_env(t_minishell *minishell)
{
	char	*old_pwd;
	char	cwd[PATH_MAX];

	getcwd(cwd, sizeof(cwd));
	old_pwd = ft_strjoin("OLDPWD=", get_env_value(minishell, "PWD"));
	if (!find_env(minishell->main_env, "OLDPWD"))
		single_export(minishell, old_pwd);
	else
		single_assign(minishell, old_pwd);
	single_assign(minishell, ft_strjoin("PWD=", cwd));
}

int	chdir_home_oldpwd(t_minishell *minishell, t_simple_cmd *curr)
{
	char	*dir_to;

	if (!(curr->arguments[1]))
	{
		if (!find_env(minishell->main_env, "HOME"))
		{
			print_error("cd", "HOME not set");
			return (1);
		}
		dir_to = get_env_value(minishell, "HOME");
	}
	else if (*curr->arguments[1] == '-')
	{
		if (!find_env(minishell->main_env, "OLDPWD"))
		{
			print_error("cd", "OLDPWD not set");
			return (1);
		}
		dir_to = get_env_value(minishell, "OLDPWD");
	}
	else
		return (0);
	chdir(dir_to);
	update_env(minishell);
	return (1);
}

void	handle_cd(t_minishell *minishell, t_simple_cmd *curr)
{
	char	*dir_to;

	if (!check_option("cd: ", curr->arguments[1]))
		return ;
	if (!chdir_home_oldpwd(minishell, curr))
	{
		dir_to = curr->arguments[1];
		if (chdir(dir_to) == -1)
		{
			errno = 0;
			print_error(dir_to, "No such file or directory");
			errno = ENOENT;
		}
		else
			update_env(minishell);
	}
}
