#include <stdio.h>

int	ft_strncmp(char *s1, char *s2, unsigned int n);

int	main(void)
{
	char			*cases[][2] = {
		{"hello", "hello"}, {"", ""}, {"abc", "abd"}, {"abd", "abc"},
		{"abc", "abcdef"}, {"abcdef", "abc"}, {"same", "samE"},
		{"42", "42"}, {"Z", "a"}
	};
	unsigned int	ns[] = {0, 1, 3, 5, 100, 4, 2, 2, 1};
	unsigned long	i;
	int				v;

	i = 0;
	while (i < sizeof(cases) / sizeof(cases[0]))
	{
		v = ft_strncmp(cases[i][0], cases[i][1], ns[i]);
		printf("case %lu: sign=%d\n", i, (v > 0) - (v < 0));
		i++;
	}
	return (0);
}
