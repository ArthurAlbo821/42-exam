#include <stdlib.h>

int	*ft_range(int start, int end)
{
	int	*tab;
	int	len;
	int	step;
	int	i;

	len = end - start;
	step = 1;
	if (len < 0)
	{
		len = -len;
		step = -1;
	}
	len++;
	tab = malloc(sizeof(int) * len);
	if (!tab)
		return (NULL);
	i = 0;
	while (i < len)
	{
		tab[i] = start + i * step;
		i++;
	}
	return (tab);
}
