#include <stdio.h>
#include <limits.h>

int	ft_is_prime(int nb);

int	main(void)
{
	int	cases[] = {0, 1, 2, 3, 4, 7, 9, 42, 97, 100, -5, 7919, INT_MAX};
	unsigned long	i;

	i = 0;
	while (i < sizeof(cases) / sizeof(cases[0]))
	{
		printf("is_prime(%d) = %d\n", cases[i], ft_is_prime(cases[i]));
		i++;
	}
	return (0);
}
