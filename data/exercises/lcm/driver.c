#include <stdio.h>

unsigned int	lcm(unsigned int a, unsigned int b);

int	main(void)
{
	unsigned int	as[] = {0, 5, 1, 4, 7, 12, 21, 100, 17};
	unsigned int	bs[] = {5, 0, 1, 6, 13, 18, 6, 80, 17};
	unsigned long	i;

	i = 0;
	while (i < sizeof(as) / sizeof(as[0]))
	{
		printf("lcm(%u, %u) = %u\n", as[i], bs[i], lcm(as[i], bs[i]));
		i++;
	}
	return (0);
}
