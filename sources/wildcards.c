/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgiordanraccoman <marvin@42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 17:20:36 by mgiordan          #+#    #+#             */
/*   Updated: 2021/06/04 17:21:01 by mgiordan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_root(char **wildcard)
{
	int		pos;
	char	*safe;

	pos = ft_find(*wildcard, '~');
	if (pos == 0)
	{
		safe = *wildcard;
		*wildcard = ft_strjoin(getenv("HOME"), *wildcard + 1);
		free(safe);
	}
	pos = ft_find(*wildcard, '*');
	if (pos == 0)
		return (ft_strdup("."));
	while (pos > 0)
	{
		if ((*wildcard)[pos] == '/')
			return (ft_strndup(*wildcard, pos + 1));
		pos--;
	}
	if ((*wildcard)[pos] == '/')
		return (ft_strdup("/"));
	return (ft_strdup("."));
}

void	list_files(t_list **list, char *root, int deep)
{
	DIR				*directory;
	struct dirent	*el;

	if (!deep || !adjust_root(&root))
	{
		free(root);
		return ;
	}
	directory = opendir(root);
	el = readdir(directory);
	while (el != NULL)
	{
		if (el->d_type == DT_REG && el->d_name[0] != '.')
		{
			if (root[0] == '.' && root[1] == '/')
				ft_lstadd_back(list, ft_lstnew(ft_strdup(el->d_name)));
			else
				ft_lstadd_back(list, ft_lstnew(ft_strjoin(root, el->d_name)));
		}
		else if (el->d_type == DT_DIR && el->d_name[0] != '.')
			list_files(list, ft_strjoin(root, el->d_name), deep - 1);
		el = readdir(directory);
	}
	closedir(directory);
	free(root);
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

	root = get_root(&wildcard);
	deep = ft_count(wildcard + ft_strlen(root), '/') + 1;
	list = NULL;
	list_files(&list, root, deep);
	ft_lstrmv_if(&list, wildcard, &filter, &free);
	if (!list)
		list = ft_lstnew(ft_strdup(wildcard));
	matrix = lst_to_matrix(list);
	ft_lstclear(&list);
	free(wildcard);
	return (ft_strjoin2D(matrix, " ", 1));
}

char	*parse_wildcards(char *input)
{
	int		i;
	char	**split;

	i = 0;
	split = ft_split(input, ' ');
	free(input);
	while (split && split[i] != NULL)
	{
		if (ft_contains(split[i], '*'))
			split[i] = expand_wc(split[i]);
		i++;
	}
	return (ft_strjoin2D(split, " ", 1));
}
