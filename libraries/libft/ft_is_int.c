/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_int.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgiordan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 16:04:54 by mgiordan          #+#    #+#             */
/*   Updated: 2021/04/14 16:04:57 by mgiordan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_is_int(long n)
{
	return (-2147483648 <= n && n <= 2147483647);
}