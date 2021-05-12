#include "minishell.h"

void    handle_pwd(t_simple_cmd *curr)
{
	char	cwd[PATH_MAX];
	char	**args;

	args = &(curr->arguments[1]);
	if (*args && is_option(*args))
		return (print_error("pwd: %s: " CC_RED "invalid option" CC_RESET "\n", *args));
	getcwd(cwd, sizeof(cwd));
	printf("%s\n", cwd);
}