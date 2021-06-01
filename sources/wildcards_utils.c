#include "minishell.h"

int	adjust_root(char **root)
{
	struct stat	sb;

	if (*root[ft_strlen(*root) - 1] != '/')
		*root = ft_strjoin(*root, "/");
	if (!stat(*root, &sb) && S_ISDIR(sb.st_mode))
		return (1);
	return (0);
}