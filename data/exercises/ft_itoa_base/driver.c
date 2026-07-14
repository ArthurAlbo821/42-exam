#include <stdio.h>
#include <stdlib.h>

char	*ft_itoa_base(int value, int base);

int	main(void)
{
	int		values[] = {0, 42, 255, -1, -42, 2147483647,
		(-2147483647 - 1), 100, 10, 6};
	int		bases[] = {2, 2, 16, 16, 10, 16, 10, 8, 7, 16};
	int		i;
	char	*res;

	i = 0;
	while (i < 10)
	{
		res = ft_itoa_base(values[i], bases[i]);
		printf("itoa_base(%d, %d) = [%s]\n", values[i], bases[i], res);
		free(res);
		i++;
	}
	return (0);
}
