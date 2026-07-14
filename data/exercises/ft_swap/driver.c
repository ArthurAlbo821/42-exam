#include <stdio.h>
#include <limits.h>

void	ft_swap(int *a, int *b);

int	main(void)
{
	int	pairs[][2] = {
		{0, 0},
		{1, 2},
		{-1, 1},
		{-42, -21},
		{42, 42},
		{INT_MIN, INT_MAX},
		{INT_MAX, INT_MIN},
		{INT_MIN, 0},
		{0, INT_MAX},
		{123456789, -987654321}
	};
	unsigned long	i;
	int				a;
	int				b;

	i = 0;
	while (i < sizeof(pairs) / sizeof(pairs[0]))
	{
		a = pairs[i][0];
		b = pairs[i][1];
		ft_swap(&a, &b);
		printf("case %lu: a=%d b=%d\n", i, a, b);
		i++;
	}
	return (0);
}
