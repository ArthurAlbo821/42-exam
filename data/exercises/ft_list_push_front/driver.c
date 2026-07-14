#include <stdio.h>
#include <stdlib.h>
#include "ft_list.h"

void	ft_list_push_front(t_list **begin_list, void *data);

static void	print_list(t_list *lst)
{
	printf("[");
	while (lst)
	{
		printf("%s", (char *)lst->data);
		if (lst->next)
			printf(", ");
		lst = lst->next;
	}
	printf("]\n");
}

static void	free_list(t_list *lst)
{
	t_list	*next;

	while (lst)
	{
		next = lst->next;
		free(lst);
		lst = next;
	}
}

int	main(void)
{
	t_list	*lst;

	lst = NULL;
	ft_list_push_front(&lst, "first");
	ft_list_push_front(&lst, "second");
	ft_list_push_front(&lst, "third");
	ft_list_push_front(&lst, "fourth");
	print_list(lst);
	ft_list_push_front(&lst, "prepended");
	print_list(lst);
	free_list(lst);
	return (0);
}
