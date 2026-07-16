#include <stdio.h>

void	ft_ft(int *nbr);

int	main(void)
{
	int	n;

	n = 0;
	ft_ft(&n);
	printf("n = %d\n", n);
	n = -100;
	ft_ft(&n);
	printf("n = %d\n", n);
	return (0);
}
