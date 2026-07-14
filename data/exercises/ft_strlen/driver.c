#include <stdio.h>

int	ft_strlen(char *str);

int	main(void)
{
	char	*cases[] = {
		"",
		"a",
		"42",
		"hello world",
		"the quick brown fox jumps over the lazy dog",
		"line\nwith\nnewlines",
		"    spaces    and	tabs	",
		"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
	};
	unsigned long	i;

	i = 0;
	while (i < sizeof(cases) / sizeof(cases[0]))
	{
		printf("len(%lu) = %d\n", i, ft_strlen(cases[i]));
		i++;
	}
	return (0);
}
