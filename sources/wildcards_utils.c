/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgiordanraccoman <marvin@42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 17:21:52 by mgiordan          #+#    #+#             */
/*   Updated: 2021/06/04 17:22:12 by mgiordan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	adjust_root(char **root)
{
	struct stat	sb;

	if ((*root)[ft_strlen(*root) - 1] != '/')
		*root = ft_append(*root, '/');
	if (!stat(*root, &sb) && S_ISDIR(sb.st_mode))
		return (1);
	return (0);
}
