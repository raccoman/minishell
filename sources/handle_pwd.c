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
