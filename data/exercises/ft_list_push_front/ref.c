#include <stdlib.h>
#include "ft_list.h"

void	ft_list_push_front(t_list **begin_list, void *data)
{
	t_list	*node;

	if (!begin_list)
		return ;
	node = malloc(sizeof(t_list));
	if (!node)
		return ;
	node->data = data;
	node->next = *begin_list;
	*begin_list = node;
}
