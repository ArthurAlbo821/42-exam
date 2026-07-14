#include <stdio.h>

unsigned char	reverse_bits(unsigned char octet);

int	main(void)
{
	unsigned char	cases[] = {0, 1, 2, 4, 8, 42, 128, 170, 85, 255};
	unsigned long	i;

	i = 0;
	while (i < sizeof(cases) / sizeof(cases[0]))
	{
		printf("reverse_bits(%u) = %u\n", (unsigned int)cases[i],
			(unsigned int)reverse_bits(cases[i]));
		i++;
	}
	return (0);
}
