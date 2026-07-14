#include <stdio.h>
#include <stdlib.h>

int	main(int argc, char **argv)
{
	int	n;
	int	div;
	int	first;

	if (argc != 2)
	{
		printf("\n");
		return (0);
	}
	n = atoi(argv[1]);
	if (n == 1)
		printf("1");
	div = 2;
	first = 1;
	while (div * div <= n)
	{
		while (n % div == 0)
		{
			if (!first)
				printf("*");
			printf("%d", div);
			first = 0;
			n = n / div;
		}
		div++;
	}
	if (n > 1)
	{
		if (!first)
			printf("*");
		printf("%d", n);
	}
	printf("\n");
	return (0);
}
