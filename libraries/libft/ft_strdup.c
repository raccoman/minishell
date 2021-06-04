/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgiordan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 15:15:01 by mgiordan          #+#    #+#             */
/*   Updated: 2021/01/12 15:15:03 by mgiordan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(char *str, int size)
{
	int		len;
	char	*new_str;
	int		i;

	len = ft_strlen(str);
	if (len < size)
		new_str = malloc(len + 1);
	else
		new_str = malloc(size + 1);
	i = 0;
	while (str[i] && i < size)
	{
		new_str[i] = str[i];
		i++;
	}
	new_str[i] = 0;
	return (new_str);
}

char	*ft_strdup(char *str)
{
	int		len;
	char	*new_str;
	int		i;

	len = ft_strlen(str);
	new_str = malloc(len + 1);
	i = 0;
	while (str[i])
	{
		new_str[i] = str[i];
		i++;
	}
	new_str[i] = 0;
	return (new_str);
}
