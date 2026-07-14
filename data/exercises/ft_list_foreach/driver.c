#include <stdio.h>
#include <stdlib.h>
#include "ft_list.h"

void	ft_list_foreach(t_list *begin_list, void (*f)(void *));

static void	print_str(void *data)
{
	printf("%s\n", (char *)data);
}

static t_list	*build(char **strs, int n)
{
	t_list	*head;
	t_list	*node;
	int		i;

	head = NULL;
	i = n - 1;
	while (i >= 0)
	{
		node = malloc(sizeof(t_list));
		node->data = strs[i];
		node->next = head;
		head = node;
		i--;
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
	char	*five[] = {"alpha", "beta", "gamma", "delta", "epsilon"};
	char	*one[] = {"solo"};
	t_list	*lst;

	printf("--- empty ---\n");
	fflush(stdout);
	ft_list_foreach(NULL, print_str);
	printf("--- single ---\n");
	lst = build(one, 1);
	fflush(stdout);
	ft_list_foreach(lst, print_str);
	free_list(lst);
	printf("--- five ---\n");
	lst = build(five, 5);
	fflush(stdout);
	ft_list_foreach(lst, print_str);
	free_list(lst);
	printf("--- end ---\n");
	return (0);
}
