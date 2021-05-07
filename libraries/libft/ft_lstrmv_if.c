#include "libft.h"

void	ft_lstrmv_if(t_list **begin_list, void *data_ref, int (*cmp)(), void (*free_fct)(void *))
{
	t_list *prec;
	t_list *tmp;
	t_list *curr;

	if (!begin_list || !(*begin_list))
		return ;
	curr = *begin_list;
	prec = NULL;
	while (curr)
	{
		if (!((*cmp)(curr->data, data_ref)))
		{
			tmp = curr->next;
			if (prec == NULL)
				*begin_list = curr->next;
			else
				prec->next = curr->next;
			(*free_fct)(curr->data);
			free(curr);
			curr = tmp;
		}
		else
		{
			prec = curr;
			curr = curr->next;
		}
	}
}