/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstrmv_if.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgiordan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 14:38:34 by mgiordan          #+#    #+#             */
/*   Updated: 2021/05/21 14:38:37 by mgiordan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstrmv_if(t_list **begin_list,
			void *data_ref, int (*cmp)(), void (*free_fct)(void *))
{
	t_list	*prec;
	t_list	*tmp;
	t_list	*curr;

	if (!begin_list || !(*begin_list))
		return ;
	curr = *begin_list;
	prec = NULL;
	while (curr)
	{
		tmp = curr->next;
		if (!((*cmp)(curr->data, data_ref)))
		{
			if (!prec)
				*begin_list = curr->next;
			else
				prec->next = curr->next;
			(*free_fct)(curr->data);
			free(curr);
		}
		else
			prec = curr;
		curr = tmp;
	}
}
