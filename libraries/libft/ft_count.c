/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgiordan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 15:51:23 by mgiordan          #+#    #+#             */
/*   Updated: 2021/06/04 15:51:28 by mgiordan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_count(char *string, int c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (string && string[i])
	{
		if (string[i] == c)
			count++;
		i++;
	}
	return (count);
}

int	ft_count_str(char *string, char *in)
{
	int	count;
	int	len;

	if (!string || !in)
		return (0);
	len = ft_strlen(in);
	count = 0;
	while (*string)
	{
		if (!ft_strncmp(string, in, len))
		{
			count++;
			string += len;
		}
		else
			string++;
	}
	return (count);
}
