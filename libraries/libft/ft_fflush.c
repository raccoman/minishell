/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fflush.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgiordan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 15:00:58 by mgiordan          #+#    #+#             */
/*   Updated: 2021/05/21 15:01:00 by mgiordan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	__sflush(FILE *fp)
{
	unsigned char	*p;
	int				n;
	int				t;

	t = fp->_flags;
	p = fp->_bf._base;
	if ((!(t & __SWR)) || !p)
		return (0);
	n = fp->_p - p;
	fp->_p = p;
	fp->_w = 0;
	if (!(t & (__SLBF | __SNBF)))
		fp->_w = fp->_bf._size;
	while (n > 0)
	{
		t = (*fp->_write)(fp->_cookie, (char *)p, n);
		if (t <= 0)
		{
			fp->_flags |= __SERR;
			return (EOF);
		}
		n -= t;
		p += t;
	}
	return (0);
}

int	ft_fflush(FILE *fp)
{
	if (fp == NULL)
		return (0);
	if ((fp->_flags & (__SWR | __SRW)) == 0)
	{
		errno = EBADF;
		return (EOF);
	}
	return (__sflush(fp));
}
