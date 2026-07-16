#include <stdio.h>

int	ft_recursive_power(int nb, int power);

int	main(void)
{
	int	pairs[][2] = {
		{2, 0}, {2, 10}, {5, 3}, {0, 0}, {0, 5},
		{1, 100}, {-2, 3}, {-2, 4}, {10, 9}, {7, -3}
	};
	unsigned long	i;

	i = 0;
	while (i < sizeof(pairs) / sizeof(pairs[0]))
	{
		printf("case %lu: %d\n", i,
			ft_recursive_power(pairs[i][0], pairs[i][1]));
		i++;
	}
	return (0);
}
