#include <stdio.h>

int	ft_ten_queens_puzzle(void);

int	main(void)
{
	int	count;

	setbuf(stdout, NULL);
	count = ft_ten_queens_puzzle();
	printf("total=%d\n", count);
	return (0);
}
