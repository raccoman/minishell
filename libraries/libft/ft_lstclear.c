/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgiordan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 12:50:56 by mgiordan          #+#    #+#             */
/*   Updated: 2021/01/14 12:50:58 by mgiordan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **element)
{
	t_list	*tmp;

	while (*element != NULL)
	{
		tmp = (*element)->next;
		free((*element)->data);
		free(*element);
		*element = tmp;
	}
}
