#include <stdio.h>
#include <stdlib.h>
#include "ft_list.h"

void	ft_list_remove_if(t_list **begin_list, void *data_ref,
		int (*cmp)(void *, void *));

static int	cmp_str(void *a, void *b)
{
	char	*s1;
	char	*s2;
	int		i;

	s1 = (char *)a;
	s2 = (char *)b;
	i = 0;
	while (s1[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
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

static void	run(char **strs, int n, char *ref)
{
	t_list	*lst;

	lst = build(strs, n);
	ft_list_remove_if(&lst, ref, cmp_str);
	printf("remove [%s]: ", ref);
	print_list(lst);
	free_list(lst);
}

int	main(void)
{
	char	*a[] = {"x", "b", "c", "d"};
	char	*b[] = {"a", "x", "c", "x"};
	char	*c[] = {"a", "b", "c", "x"};
	char	*d[] = {"x", "x", "x", "x"};
	char	*e[] = {"a", "b", "c", "d"};

	run(a, 4, "x");
	run(b, 4, "x");
	run(c, 4, "x");
	run(d, 4, "x");
	run(e, 4, "z");
	return (0);
}
