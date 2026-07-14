#include <stdio.h>
#include <stdlib.h>
#include "list.h"

int	cycle_detector(const t_list *list);

static t_list	*make(int n)
{
	t_list	*head;
	t_list	*node;
	int		i;

	head = NULL;
	i = n;
	while (i > 0)
	{
		node = malloc(sizeof(t_list));
		node->data = i;
		node->next = head;
		head = node;
		i--;
	}
	return (head);
}

static t_list	*nth(t_list *head, int idx)
{
	while (idx > 0 && head)
	{
		head = head->next;
		idx--;
	}
	return (head);
}

static t_list	*tail(t_list *head)
{
	while (head && head->next)
		head = head->next;
	return (head);
}

int	main(void)
{
	t_list	*l0;
	t_list	*l1;
	t_list	*l5;

	l0 = NULL;
	printf("empty: %d\n", cycle_detector(l0));
	l1 = make(1);
	printf("single acyclic: %d\n", cycle_detector(l1));
	l5 = make(5);
	printf("five acyclic: %d\n", cycle_detector(l5));
	tail(l5)->next = l5;
	printf("tail->head: %d\n", cycle_detector(l5));
	l5 = make(5);
	tail(l5)->next = nth(l5, 2);
	printf("tail->middle: %d\n", cycle_detector(l5));
	l1 = make(1);
	l1->next = l1;
	printf("self-loop single: %d\n", cycle_detector(l1));
	return (0);
}
