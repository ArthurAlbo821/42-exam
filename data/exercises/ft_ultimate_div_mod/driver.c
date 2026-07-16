#include <stdio.h>

void	ft_ultimate_div_mod(int *a, int *b);

int	main(void)
{
	int				pairs[][2] = {
		{42, 5}, {10, 3}, {-17, 4}, {17, -4},
		{-17, -4}, {0, 7}, {100, 10}, {7, 8}
	};
	unsigned long	i;
	int				a;
	int				b;

	i = 0;
	while (i < sizeof(pairs) / sizeof(pairs[0]))
	{
		a = pairs[i][0];
		b = pairs[i][1];
		ft_ultimate_div_mod(&a, &b);
		printf("case %lu: a=%d b=%d\n", i, a, b);
		i++;
	}
	return (0);
}
