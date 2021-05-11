#include "minishell.h"

int	is_empty(char **args)
{
	int	k;

	if (!args[0])
		return (1);
	k = 0;
	while (args[0][k])
	{
		if (!ft_isspace(args[0][k]))
			return (0);
		k++;
	}
	return (1);
}

void	update_env(t_minishell *minishell, char *new)
{
	char	*old_pwd;
	char 	*new_pwd;

	new_pwd = ft_strdup(new);
	old_pwd = ft_strjoin("OLDPWD=", get_env_value(minishell, "PWD"));
	if (!find_env(minishell->main_env, "OLDPWD"))
		single_export(minishell, old_pwd);
	else
		single_assign(minishell, old_pwd);
	single_assign(minishell, ft_strjoin("PWD=", new_pwd));
}

void	handle_cd(t_minishell *minishell, t_simple_cmd *curr)
{
	char	*dir_to;
	char	cwd[PATH_MAX];
	char	**args;

	args = &(curr->arguments[1]);
	if (!(*args))
	{
		if (!find_env(minishell->main_env, "HOME"))
		{
			printf(CC_WHT "cd: " CC_RED "HOME not set" CC_RESET "\n");
			return ;
		}
		dir_to = getenv("HOME");
	}
	else
		dir_to = *args;
	if (chdir(dir_to) == -1)
		printf(CC_WHT "cd: " CC_RED "%s" CC_RESET "\n", strerror(errno));
	else
	{
		getcwd(cwd, sizeof(cwd));
		update_env(minishell, cwd);
	}
}