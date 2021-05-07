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

char	*ft_strdup(const char *str)
{
	char	*copy;
	int		size;
	int		i;

	size = ft_strlen(str) + 1;
	copy = malloc(size);
	i = -1;
	while (++i < size)
		copy[i] = str[i];
	copy[i] = 0;
	return (copy);
}
