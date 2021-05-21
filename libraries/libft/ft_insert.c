/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_insert.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgiordan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 14:49:54 by mgiordan          #+#    #+#             */
/*   Updated: 2021/05/21 14:49:56 by mgiordan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*__new_str(char c)
{
	char	*str;

	str = malloc(sizeof(char) * 2);
	if (!str)
		return (NULL);
	str[0] = c;
	str[1] = '\0';
	return (str);
}

char	*ft_insert(char *str, int c, int pos)
{
	char	*new_str;
	int		i;

	if (!str)
		return (__new_str(c));
	i = 0;
	new_str = malloc(sizeof(char) * (ft_strlen(str) + 2));
	while (str[i] && i < pos)
	{
		new_str[i] = str[i];
		i++;
	}
	new_str[i] = c;
	i--;
	while (str[++i])
		new_str[i + 1] = str[i];
	new_str[i + 1] = 0;
	free(str);
	return (new_str);
}
