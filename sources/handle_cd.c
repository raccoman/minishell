#include "minishell.h"

void	update_env(t_minishell *minishell, char *new)
{
	char	*old_pwd;

	old_pwd = ft_strjoin("OLDPWD=", get_env_value(minishell, "PWD"));
	if (!find_env(minishell->main_env, "OLDPWD"))
		single_export(minishell, old_pwd);
	else
		single_assign(minishell, old_pwd);
	single_assign(minishell, ft_strjoin("PWD=", new));
}

void	handle_cd(t_minishell *minishell, t_simple_cmd *curr)
{
	char	*dir_to;
	char	cwd[PATH_MAX];

	if (!check_option("cd: ", curr->arguments[1]))
		return ;
	if (!(curr->arguments[1]))
	{
		if (!find_env(minishell->main_env, "HOME"))
			return (print_error("cd", "HOME not set"));
		dir_to = getenv("HOME");
	}
	else
		dir_to = curr->arguments[1];
	if (chdir(dir_to) == -1)
	{
		errno = 0;
		print_error(dir_to, "No such file or directory");
		errno = ENOENT;
	}
	else
	{
		getcwd(cwd, sizeof(cwd));
		update_env(minishell, cwd);
	}
}
