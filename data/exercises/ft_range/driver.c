#include <stdio.h>
#include <stdlib.h>

int	*ft_range(int start, int end);

void	run_case(int start, int end)
{
	int	*tab;
	int	len;
	int	i;

	tab = ft_range(start, end);
	len = end - start;
	if (len < 0)
		len = -len;
	len++;
	printf("range(%d, %d):", start, end);
	i = 0;
	while (i < len)
	{
		printf(" %d", tab[i]);
		i++;
	}
	printf("\n");
	free(tab);
}

int	main(void)
{
	run_case(1, 3);
	run_case(-3, 1);
	run_case(0, 0);
	run_case(0, -3);
	run_case(5, 3);
	return (0);
}
