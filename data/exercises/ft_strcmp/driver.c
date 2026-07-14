#include <stdio.h>

int	ft_strcmp(char *s1, char *s2);

/*
** Valid implementations may differ in magnitude, so only the sign of the
** return value is printed.
*/

int	main(void)
{
	char	*cases[][2] = {
		{"hello", "hello"},
		{"", ""},
		{"", "a"},
		{"a", ""},
		{"abc", "abd"},
		{"abd", "abc"},
		{"abc", "abcdef"},
		{"abcdef", "abc"},
		{"a", "b"},
		{"b", "a"},
		{"same start different end", "same start different enD"},
		{"42 school", "42 school"},
		{"Z", "a"}
	};
	unsigned long	i;
	int				v;

	i = 0;
	while (i < sizeof(cases) / sizeof(cases[0]))
	{
		v = ft_strcmp(cases[i][0], cases[i][1]);
		printf("case %lu: sign=%d\n", i, (v > 0) - (v < 0));
		i++;
	}
	return (0);
}
