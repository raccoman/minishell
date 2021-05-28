#include "minishell.h"

char	*get_root(char *wildcard)
{
	int		offset;
	char	*root;
	char	*prefix;

	prefix = ft_split(wildcard, '*')[0];
	if (!prefix || prefix[0] == '*')
		return (ft_strdup("."));
	offset = ft_strlen(prefix);
	while (prefix[--offset])
		if (prefix[offset] == '/')
			break;
	root = malloc(sizeof(char) * (offset));
	if (root)
	{
		ft_memcpy(root, prefix, offset);
		root[offset] = 0;
	}
	return (root);
}

void	list_files(t_list **list, char *root, int deep)
{
	DIR				*directory;
	struct dirent	*element;
	char			*base_dir;

	if (deep == 0)
		return ;
	directory = opendir(root);
	if (!directory)
		return ;
	base_dir = ft_strjoin(root, "/");
	element = readdir(directory);
	while (element != NULL)
	{
		if (element->d_type == DT_REG && element->d_name[0] != '.')
			ft_lstadd_back(list, ft_lstnew(ft_strjoin(base_dir, element->d_name)));
		else if (element->d_type == DT_DIR && element->d_name[0] != '.')
			list_files(list, ft_strjoin(base_dir, element->d_name), deep - 1);
		element = readdir(directory);
	}
	free(base_dir);
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
	t_list			*list;
	int				deep;
	char			*root;

	root = get_root(wildcard);
	deep = ft_count(wildcard + ft_strlen(root), '/') + 1;
	list_files(&list, root, deep);
	ft_lstrmv_if(&list, ft_strjoin(wildcard, "/*"), filter, &free);
	//TODO: PERCHE CAZZO CRASHA??!?!?!?
	return (ft_strdup("wc")); //TODO: join list by ' '
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