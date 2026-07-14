#include <stdio.h>

int	ft_fibonacci(int index);

int	main(void)
{
	int	cases[] = {-3, 0, 1, 2, 3, 10, 15, 20};
	unsigned long	i;

	i = 0;
	while (i < sizeof(cases) / sizeof(cases[0]))
	{
		printf("ft_fibonacci(%d) = %d\n", cases[i], ft_fibonacci(cases[i]));
		i++;
	}
	return (0);
}
