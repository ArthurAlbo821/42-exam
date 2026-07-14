#include <stdio.h>

int	ft_iterative_power(int nb, int power);

int	main(void)
{
	int	cases[][2] = {
		{2, 10},
		{0, 0},
		{5, 1},
		{1, 20},
		{-2, 3},
		{-2, 4},
		{3, -2},
		{0, 5},
		{10, 0},
		{7, 3}
	};
	unsigned long	i;

	i = 0;
	while (i < sizeof(cases) / sizeof(cases[0]))
	{
		printf("power(%d, %d) = %d\n", cases[i][0], cases[i][1],
			ft_iterative_power(cases[i][0], cases[i][1]));
		i++;
	}
	return (0);
}
