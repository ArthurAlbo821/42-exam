#include <stdio.h>
#include <stdlib.h>

char	*ft_convert_base(char *nbr, char *base_from, char *base_to);

void	show(int n, char *nbr, char *bf, char *bt)
{
	char	*r;

	r = ft_convert_base(nbr, bf, bt);
	printf("case %d: [%s]\n", n, r ? r : "(null)");
	free(r);
}

int	main(void)
{
	show(0, "42", "0123456789", "01");
	show(1, "FF", "0123456789ABCDEF", "0123456789");
	show(2, "  ---+42", "0123456789", "0123456789");
	show(3, "-2147483648", "0123456789", "0123456789");
	show(4, "101010", "01", "0123456789ABCDEF");
	show(5, "0", "0123456789", "01");
	show(6, "42", "0123456789", "1");
	show(7, "42", "001", "01");
	return (0);
}
