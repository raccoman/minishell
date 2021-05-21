/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgiordan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 11:39:31 by mgiordan          #+#    #+#             */
/*   Updated: 2021/01/13 11:39:34 by mgiordan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	abs(int n)
{
	if (n < 0)
		n *= -1;
	return (n);
}

int	calc_digits(int n, short *negative)
{
	int	count;

	*negative = 0;
	if (n < 0)
		*negative = 1;
	if (n == 0)
		return (1);
	count = 0;
	while (n != 0)
	{
		count++;
		n /= 10;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	short	negative;
	int		digit_count;
	char	*converted;

	digit_count = calc_digits(n, &negative) + 1;
	if (negative)
		digit_count++;
	converted = malloc(digit_count);
	converted[digit_count - 1] = 0;
	if (!n)
	{
		converted[digit_count - 2] = '0';
		return (converted);
	}
	digit_count -= 2;
	while (n)
	{
		converted[digit_count--] = abs(n % 10) + 48;
		n /= 10;
	}
	if (negative)
		converted[digit_count] = '-';
	return (converted);
}
