#include "minishell.h"

short	is_option(char *str)
{
	if (*str == '-')
		return (1);
	return (0);
}

void    handle_pwd(t_simple_cmd *curr)
{
	char	cwd[PATH_MAX];
	char	**args;

	printf(CC_RESET);
	args = &(curr->arguments[1]);
	if (*args && is_option(*args))
	{
		printf("pwd: %s: " CC_RED "invalid option" CC_RESET "\n", *args);
		return ;
	}
	getcwd(cwd, sizeof(cwd));
	printf("%s\n", cwd);
}