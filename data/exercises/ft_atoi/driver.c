#include <stdio.h>

int	ft_atoi(const char *str);

int	main(void)
{
	const char	*cases[] = {
		"42",
		"   -42",
		"+1234ab567",
		"0",
		"-0",
		"2147483647",
		"-2147483648",
		"abc",
		"",
		"  +  5",
		"12 34",
		"\t\n\v\f\r 999xyz"
	};
	unsigned long	i;

	i = 0;
	while (i < sizeof(cases) / sizeof(cases[0]))
	{
		printf("case %lu: %d\n", i, ft_atoi(cases[i]));
		i++;
	}
	return (0);
}
