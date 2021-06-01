#include "minishell.h"
#include "wildcards_utils.c"

char	*get_root(char *wildcard)
{
	int pos;

	pos = ft_find(wildcard, '*');
	if (pos == 0)
		return (strdup("."));
	while (pos > 0)
	{
		if (wildcard[pos] == '/')
			return (strndup(wildcard, pos + 1));
		pos--;
	}
	if (wildcard[pos] == '/')
		return (strdup("/"));
	return (strdup("."));
}

void	list_files(t_list **list, char *root, int deep)
{
	DIR				*directory;
	struct dirent	*element;

	if (deep == 0)
		return ;
	if (!adjust_root(&root))
		return ;
	directory = opendir(root);
	if (!directory)
		return ;
	element = readdir(directory);
	while (element != NULL)
	{
		if (element->d_type == DT_REG && element->d_name[0] != '.')
		{
			if (root[0] == '.' && root[1] == '/')
				ft_lstadd_back(list, ft_lstnew(ft_strdup(element->d_name)));
			else
				ft_lstadd_back(list, ft_lstnew(ft_strjoin(root, element->d_name)));
		}
		else if (element->d_type == DT_DIR && element->d_name[0] != '.')
			list_files(list, ft_strjoin(root, element->d_name), deep - 1);
		element = readdir(directory);
	}
	closedir(directory);
}

int	filter(const char *file, const char *wildcard)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	while (file[i])
	{
		if (wildcard[k] == '*')
		{
			k++;
			while (file[i] && file[i] != wildcard[k])
				i++;
		}
		if (wildcard[k] != file[i])
			return (0);
		k++;
		i++;
	}
	if (file[i] != wildcard[k])
		return (0);
	return (1);
}

char	*expand_wc(char *wildcard)
{
	t_list	*list;
	int		deep;
	char	*root;
	char	**matrix;

	root = get_root(wildcard);
	deep = ft_count(wildcard + ft_strlen(root), '/') + 1;
	list = NULL;
	list_files(&list, root, deep);
	ft_lstrmv_if(&list, wildcard, &filter, &free);
	matrix = lst_to_matrix(list);
	return (ft_strjoin2D(matrix, " ", 1));
}

char	*parse_wildcards(char *input)
{
	int	i;
	char	**split;

	i = 0;
	split = ft_split(input, ' ');
	while (split && split[i] != NULL)
	{
		if (ft_contains(split[i], '*'))
			split[i] = expand_wc(split[i]);
		i++;
	}
	return (ft_strjoin2D(split, " ", 1));
}