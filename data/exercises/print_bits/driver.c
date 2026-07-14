#include <stdio.h>

void	print_bits(unsigned char octet);

int	main(void)
{
	unsigned char	cases[] = {0, 1, 2, 4, 8, 42, 128, 255, 170, 85};
	unsigned long	i;

	i = 0;
	while (i < sizeof(cases) / sizeof(cases[0]))
	{
		printf("case %lu (%u): ", i, cases[i]);
		fflush(stdout);
		print_bits(cases[i]);
		printf("\n");
		fflush(stdout);
		i++;
	}
	return (0);
}
