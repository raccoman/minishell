/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_replace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgiordan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 15:26:12 by mgiordan          #+#    #+#             */
/*   Updated: 2021/06/10 15:26:15 by mgiordan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_replace(char **string, char *match, char *replacement)
{
	char	*safe;
	char	*new;
	int		i;

	i = 0;
	new = NULL;
	while ((*string)[i])
	{
		if (!ft_strncmp((*string) + i, match, ft_strlen(match)))
		{
			safe = new;
			new = ft_strjoin(new, replacement);
			if (safe)
				free(safe);
			i += ft_strlen(match);
		}
		else
			new = ft_append(new, (*string)[i++]);
	}
	free(*string);
	*string = new;
}
