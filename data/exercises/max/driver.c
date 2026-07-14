#include <stdio.h>
#include <limits.h>

int	max(int *tab, unsigned int len);

int	main(void)
{
	int	t0[] = {42};
	int	t1[] = {7};
	int	t2[] = {-5, -2, -9, -100};
	int	t3[] = {INT_MIN, 0, INT_MAX, -42};
	int	t4[] = {3, 9, 9, 1, 9, 2};
	int	t5[] = {100, 1, 2, 3};
	int	t6[] = {1, 2, 100, 3, 4};
	int	t7[] = {1, 2, 3, 100};
	int	t8[] = {INT_MIN, INT_MIN, -2147483647};

	printf("case 0 (len 0): %d\n", max(t0, 0));
	printf("case 1 (single): %d\n", max(t1, 1));
	printf("case 2 (all negative): %d\n", max(t2, 4));
	printf("case 3 (INT_MIN/INT_MAX): %d\n", max(t3, 4));
	printf("case 4 (duplicates): %d\n", max(t4, 6));
	printf("case 5 (max at start): %d\n", max(t5, 4));
	printf("case 6 (max in middle): %d\n", max(t6, 5));
	printf("case 7 (max at end): %d\n", max(t7, 4));
	printf("case 8 (INT_MIN only): %d\n", max(t8, 3));
	return (0);
}
