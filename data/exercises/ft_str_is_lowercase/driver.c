#include <stdio.h>

int	ft_str_is_lowercase(char *str);

int	main(void)
{
	char			*cases[] = {"", "abc", "ABC", "abcABC", "abc123", "12345", "hello world", "42", "!@#", "aA", "  ", "z"};
	unsigned long	i;

	i = 0;
	while (i < sizeof(cases) / sizeof(cases[0]))
	{
		printf("[%s] = %d\n", cases[i], ft_str_is_lowercase(cases[i]));
		i++;
	}
	return (0);
}
