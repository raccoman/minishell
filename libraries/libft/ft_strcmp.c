/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgiordan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 13:40:56 by mgiordan          #+#    #+#             */
/*   Updated: 2021/04/15 13:40:59 by mgiordan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tolower(int c)
{
	return (c + ((c >= 'A' && c <= 'Z') ? 32 : 0));
}

int	ft_strcmp(char *str1, char *str2)
{
	while (*str1 && *str2 && *str1 == *str2)
	{
		str1++;
		str2++;
	}
	if (!(*str1) && !(*str2))
		return (0);
	return (1);
}

int	ft_strcmp_cins(const char *str1, const char *str2)
{
	while (*str1 && *str2 && ft_tolower(*str1) == ft_tolower(*str2))
	{
		str1++;
		str2++;
	}
	if (!(*str1) && !(*str2))
		return (0);
	return (1);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t index;

	if (n <= 0)
		return (0);
	index = 0;
	while (index < n)
	{
		if ((unsigned char)s1[index] == 0 || (unsigned char)s2[index] == 0)
			return ((unsigned char)s1[index] - (unsigned char)s2[index]);
		if ((unsigned char)s1[index] != (unsigned char)s2[index])
			return ((unsigned char)s1[index] - (unsigned char)s2[index]);
		index++;
	}
	return (0);
}