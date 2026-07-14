#include <stdio.h>
#include <stdlib.h>
#include "ft_list.h"

int	ft_list_size(t_list *begin_list);

static t_list	*make_list(int n)
{
	t_list	*head;
	t_list	*node;
	int		i;

	head = NULL;
	i = 0;
	while (i < n)
	{
		node = malloc(sizeof(t_list));
		node->data = NULL;
		node->next = head;
		head = node;
		i++;
	}
	return (head);
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
	t_list	*l0;
	t_list	*l1;
	t_list	*l5;

	l0 = make_list(0);
	l1 = make_list(1);
	l5 = make_list(5);
	printf("size(0 nodes) = %d\n", ft_list_size(l0));
	printf("size(1 node)  = %d\n", ft_list_size(l1));
	printf("size(5 nodes) = %d\n", ft_list_size(l5));
	free_list(l0);
	free_list(l1);
	free_list(l5);
	return (0);
}
