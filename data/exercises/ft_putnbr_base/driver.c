#include <stdio.h>

void	ft_putnbr_base(int nbr, char *base);

void	show(int n, int nbr, char *base)
{
	printf("case %d: ", n);
	ft_putnbr_base(nbr, base);
	printf("\n");
}

int	main(void)
{
	setbuf(stdout, NULL);
	show(0, 42, "0123456789");
	show(1, -42, "0123456789");
	show(2, 42, "01");
	show(3, 255, "0123456789ABCDEF");
	show(4, 42, "poneyvif");
	show(5, -2147483648, "0123456789");
	show(6, 42, "");
	show(7, 42, "1");
	show(8, 42, "0110");
	show(9, 42, "01+");
	return (0);
}
