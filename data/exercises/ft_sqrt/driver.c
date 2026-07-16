#include <stdio.h>
#include <limits.h>

int	ft_sqrt(int nb);

int	main(void)
{
	int	cases[] = {0, 1, 4, 9, 15, 16, 42, 144, 2147395600, -4, INT_MAX};
	unsigned long	i;

	i = 0;
	while (i < sizeof(cases) / sizeof(cases[0]))
	{
		printf("sqrt(%d) = %d\n", cases[i], ft_sqrt(cases[i]));
		i++;
	}
	return (0);
}
