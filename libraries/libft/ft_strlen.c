/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgiordan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 16:18:13 by mgiordan          #+#    #+#             */
/*   Updated: 2021/01/11 16:27:07 by mgiordan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strlen(const char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_strlen_skipspaces(char *string)
{
	char	*safe;
	int		len;

	safe = ft_strdup(string);
	ft_replace(&safe, " ", NULL);
	len = ft_strlen(safe);
	free(safe);
	return (len);
}
