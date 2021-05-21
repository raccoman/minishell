/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove_at.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgiordan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 14:36:45 by mgiordan          #+#    #+#             */
/*   Updated: 2021/05/21 14:36:49 by mgiordan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_remove_at(char *str, int pos)
{
	int		i;
	char	*new_str;

	i = 0;
	new_str = malloc(ft_strlen(str) * sizeof(char));
	while (str[i] && i < pos)
	{
		new_str[i] = str[i];
		i++;
	}
	while (str[i + 1])
	{
		new_str[i] = str[i + 1];
		i++;
	}
	free(str);
	new_str[i] = 0;
	return (new_str);
}
