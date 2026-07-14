#include <stdio.h>
#include <stdlib.h>

char	*ft_strdup(char *src);

int	main(void)
{
	char	*cases[] = {
		"",
		"a",
		"42",
		"hello world",
		"  leading and trailing spaces  ",
		"the quick brown fox jumps over the lazy dog 0123456789"
	};
	char	original[] = "immutable";
	char	*dup;
	unsigned long	i;

	i = 0;
	while (i < sizeof(cases) / sizeof(cases[0]))
	{
		dup = ft_strdup(cases[i]);
		printf("case %lu: [%s]\n", i, dup);
		free(dup);
		i++;
	}
	dup = ft_strdup(original);
	dup[0] = 'X';
	printf("separate memory: original=[%s] dup=[%s]\n", original, dup);
	free(dup);
	return (0);
}
