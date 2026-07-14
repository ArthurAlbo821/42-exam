#include <stdio.h>

void	ft_putstr(char *str);

int	main(void)
{
	char	*cases[] = {
		"",
		"x",
		"Hello, World!",
		"line\nbreak\tand tab",
		"42",
		"   leading and trailing spaces   ",
		"the quick brown fox jumps over the lazy dog",
		"punctuation: !@#$%^&*()_+-=[]{};'\",.<>/?",
		"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
		"multiple words separated by single spaces"
	};
	unsigned long	i;

	i = 0;
	while (i < sizeof(cases) / sizeof(cases[0]))
	{
		printf("case %lu: <", i);
		fflush(stdout);
		ft_putstr(cases[i]);
		fflush(stdout);
		printf(">\n");
		fflush(stdout);
		i++;
	}
	return (0);
}
