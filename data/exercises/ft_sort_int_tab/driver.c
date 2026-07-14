#include <stdio.h>
#include <limits.h>

void	ft_sort_int_tab(int *tab, int size);

void	run_case(char *label, int *tab, int size)
{
	int	i;

	ft_sort_int_tab(tab, size);
	printf("%s:", label);
	i = 0;
	while (i < size)
	{
		printf(" %d", tab[i]);
		i++;
	}
	printf("\n");
}

int	main(void)
{
	int	t0[] = {42};
	int	t1[] = {5};
	int	t2[] = {1, 2, 3, 4, 5};
	int	t3[] = {5, 4, 3, 2, 1};
	int	t4[] = {3, 1, 3, 2, 3, 1};
	int	t5[] = {-4, 7, -12, 0, -1};
	int	t6[] = {9, -3, 42, 0, INT_MAX, INT_MIN, 7, -3, 21, 1};

	run_case("case 0 (empty)", t0, 0);
	run_case("case 1 (single)", t1, 1);
	run_case("case 2 (sorted)", t2, 5);
	run_case("case 3 (reverse)", t3, 5);
	run_case("case 4 (duplicates)", t4, 6);
	run_case("case 5 (negatives)", t5, 5);
	run_case("case 6 (size 10)", t6, 10);
	return (0);
}
