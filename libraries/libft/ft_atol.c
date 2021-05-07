/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgiordan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 16:04:44 by mgiordan          #+#    #+#             */
/*   Updated: 2021/04/14 16:04:46 by mgiordan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

short	ft_isspace(char c)
{
	int		i;
	char	*spaces;

	spaces = " \f\n\r\t\v";
	i = 0;
	while (spaces[i] != '\0')
	{
		if (spaces[i] == c)
			return (1);
		i++;
	}
	return (0);
}

long	ft_atol(const char *num)
{
	long	return_value;
	short	negative;
	int		i;

	return_value = 0;
	negative = 1;
	i = 0;
	while (ft_isspace(num[i]))
		i++;
	if (num[i] == '-' || num[i] == '+')
	{
		if (num[i++] == '-')
			negative = -1;
	}
	while ('0' <= num[i] && num[i] <= '9')
	{
		return_value *= 10;
		return_value += num[i] - 48;
		i++;
	}
	return (return_value * negative);
}
