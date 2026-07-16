#include <stdio.h>
#include <limits.h>

void	ft_rev_int_tab(int *tab, int size);

void	run_case(char *label, int *tab, int size)
{
	int	i;

	ft_rev_int_tab(tab, size);
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
	int	t1[] = {1, 2};
	int	t2[] = {1, 2, 3, 4, 5};
	int	t3[] = {1, 2, 3, 4};
	int	t4[] = {-4, 7, -12, 0, INT_MAX, INT_MIN};

	run_case("case 0 (single)", t0, 1);
	run_case("case 1 (pair)", t1, 2);
	run_case("case 2 (odd)", t2, 5);
	run_case("case 3 (even)", t3, 4);
	run_case("case 4 (mixed)", t4, 6);
	return (0);
}
