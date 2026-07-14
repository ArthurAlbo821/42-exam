#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

char	*ft_itoa(int nbr);

int	main(void)
{
	int				cases[] = {
		0, 42, -42, 7, -7, INT_MAX, INT_MIN, 1000000, -1
	};
	char			*str;
	unsigned long	i;

	i = 0;
	while (i < sizeof(cases) / sizeof(cases[0]))
	{
		str = ft_itoa(cases[i]);
		printf("itoa(%d) = [%s]\n", cases[i], str);
		free(str);
		i++;
	}
	return (0);
}
