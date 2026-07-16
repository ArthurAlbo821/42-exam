#include <stdio.h>
#include <limits.h>

void	ft_putnbr(int nb);

void	show(int n, int nb)
{
	printf("case %d: ", n);
	ft_putnbr(nb);
	printf("\n");
}

int	main(void)
{
	setbuf(stdout, NULL);
	show(0, 0);
	show(1, 42);
	show(2, -42);
	show(3, 7);
	show(4, -1000);
	show(5, 2147483647);
	show(6, -2147483648);
	return (0);
}
