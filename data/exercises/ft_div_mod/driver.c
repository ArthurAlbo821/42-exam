#include <stdio.h>

void	ft_div_mod(int a, int b, int *div, int *mod);

int	main(void)
{
	int				pairs[][2] = {
		{42, 5}, {10, 3}, {-17, 4}, {17, -4},
		{-17, -4}, {0, 7}, {100, 10}, {7, 8}
	};
	unsigned long	i;
	int				div;
	int				mod;

	i = 0;
	while (i < sizeof(pairs) / sizeof(pairs[0]))
	{
		ft_div_mod(pairs[i][0], pairs[i][1], &div, &mod);
		printf("case %lu: div=%d mod=%d\n", i, div, mod);
		i++;
	}
	return (0);
}
