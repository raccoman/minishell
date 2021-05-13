#include "minishell.h"

void    handle_pwd(t_simple_cmd *curr)
{
	char	cwd[PATH_MAX];
	char	**args;
	char	*error_prefix;

	args = &(curr->arguments[1]);
	if (*args && is_option(*args))
	{
		error_prefix = ft_strjoin("pwd: ", *args);
		print_error(error_prefix, "Invalid option");
		free(error_prefix);
		errno = 1;
		return ;
	}
	getcwd(cwd, sizeof(cwd));
	printf("%s\n", cwd);
}