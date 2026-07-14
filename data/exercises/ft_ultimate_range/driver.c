#include <stdio.h>
#include <stdlib.h>

int	ft_ultimate_range(int **range, int min, int max);

int	main(void)
{
	static int	poison;
	int			mins[] = {0, -3, 0, 5, 10};
	int			maxs[] = {5, 2, 0, 2, 11};
	int			*range;
	int			size;
	int			i;
	int			j;

	i = 0;
	while (i < 5)
	{
		range = &poison;
		size = ft_ultimate_range(&range, mins[i], maxs[i]);
		printf("range(%d, %d): size=%d, values=", mins[i], maxs[i], size);
		if (range == NULL)
			printf("null");
		else
		{
			j = 0;
			while (j < size)
			{
				printf(" %d", range[j]);
				j++;
			}
			if (range != &poison)
				free(range);
		}
		printf("\n");
		i++;
	}
	return (0);
}
