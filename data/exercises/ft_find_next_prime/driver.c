#include <stdio.h>

int	ft_find_next_prime(int nb);

int	main(void)
{
	int	cases[] = {0, 1, 2, 3, 4, 14, 20, 42, 97, 98, -10, 7918};
	unsigned long	i;

	i = 0;
	while (i < sizeof(cases) / sizeof(cases[0]))
	{
		printf("next_prime(%d) = %d\n", cases[i],
			ft_find_next_prime(cases[i]));
		i++;
	}
	return (0);
}
