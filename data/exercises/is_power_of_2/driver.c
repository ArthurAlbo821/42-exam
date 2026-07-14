#include <stdio.h>

int	is_power_of_2(unsigned int n);

int	main(void)
{
	unsigned int	cases[] = {
		0u, 1u, 2u, 3u, 4u, 5u, 8u, 64u, 100u, 1024u,
		2147483648u, 4294967295u
	};
	unsigned long	i;

	i = 0;
	while (i < sizeof(cases) / sizeof(cases[0]))
	{
		printf("is_power_of_2(%u) = %d\n", cases[i], is_power_of_2(cases[i]));
		i++;
	}
	return (0);
}
