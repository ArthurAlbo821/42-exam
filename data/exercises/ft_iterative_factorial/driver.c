#include <stdio.h>

int	ft_iterative_factorial(int nb);

int	main(void)
{
	int	cases[] = {-5, -1, 0, 1, 2, 5, 6, 7, 10, 12};
	unsigned long	i;

	i = 0;
	while (i < sizeof(cases) / sizeof(cases[0]))
	{
		printf("factorial(%d) = %d\n", cases[i], ft_iterative_factorial(cases[i]));
		i++;
	}
	return (0);
}
