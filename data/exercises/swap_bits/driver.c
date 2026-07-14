#include <stdio.h>

unsigned char	swap_bits(unsigned char octet);

int	main(void)
{
	unsigned char	cases[] = {0, 1, 15, 16, 65, 170, 240, 255, 66};
	unsigned long	i;

	i = 0;
	while (i < sizeof(cases) / sizeof(cases[0]))
	{
		printf("swap_bits(%u) = %u\n", (unsigned int)cases[i],
			(unsigned int)swap_bits(cases[i]));
		i++;
	}
	return (0);
}
