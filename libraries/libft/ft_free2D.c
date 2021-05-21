/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free2D.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgiordan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 14:51:20 by mgiordan          #+#    #+#             */
/*   Updated: 2021/05/21 14:51:22 by mgiordan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free2D(void **buffer)
{
	int				i;
	unsigned char	**mem;

	if (buffer != NULL)
	{
		i = 0;
		mem = (unsigned char **)buffer;
		while (mem[i] != 0)
			free(mem[i++]);
		free(mem);
	}
}
