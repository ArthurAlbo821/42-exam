#include <stdlib.h>
#include "ft_list.h"

void	ft_list_remove_if(t_list **begin_list, void *data_ref,
		int (*cmp)(void *, void *))
{
	t_list	*cur;
	t_list	*next;

	if (!begin_list)
		return ;
	while (*begin_list && cmp((*begin_list)->data, data_ref) == 0)
	{
		next = (*begin_list)->next;
		free(*begin_list);
		*begin_list = next;
	}
	cur = *begin_list;
	while (cur && cur->next)
	{
		if (cmp(cur->next->data, data_ref) == 0)
		{
			next = cur->next->next;
			free(cur->next);
			cur->next = next;
		}
		else
			cur = cur->next;
	}
}
