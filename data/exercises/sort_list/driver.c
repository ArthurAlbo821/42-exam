#include <stdio.h>
#include <stdlib.h>
#include "ft_list.h"

t_list	*sort_list(t_list *lst, int (*cmp)(int, int));

static int	ascending(int a, int b)
{
	return (a <= b);
}

static int	descending(int a, int b)
{
	return (a >= b);
}

static t_list	*build(int *vals, int n)
{
	t_list	*head;
	t_list	*node;
	int		i;

	head = NULL;
	i = n - 1;
	while (i >= 0)
	{
		node = malloc(sizeof(t_list));
		node->data = vals[i];
		node->next = head;
		head = node;
		i--;
	}
	return (head);
}

static void	print_list(t_list *lst)
{
	printf("[");
	while (lst)
	{
		printf("%d", lst->data);
		if (lst->next)
			printf(" ");
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

static void	run(int *vals, int n)
{
	t_list	*lst;

	lst = build(vals, n);
	lst = sort_list(lst, ascending);
	printf("asc:  ");
	print_list(lst);
	lst = sort_list(lst, descending);
	printf("desc: ");
	print_list(lst);
	free_list(lst);
}

int	main(void)
{
	int	a[] = {5, 3, 8, 1, 3, 9, 2, 3};
	int	b[] = {1, 2, 3, 4, 5};
	int	c[] = {5, 4, 3, 2, 1};
	int	d[] = {42};

	run(a, 8);
	run(b, 5);
	run(c, 5);
	run(d, 1);
	printf("null: ");
	print_list(sort_list(NULL, ascending));
	return (0);
}
