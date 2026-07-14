#include <stdio.h>

char	*ft_strcpy(char *s1, char *s2);

int	main(void)
{
	char	*cases[] = {
		"",
		"a",
		"42",
		"hello",
		"Hello, World!",
		"a string with several spaces in it",
		"   leading and trailing spaces   ",
		"tabs\tand\nnewlines inside",
		"the quick brown fox jumps over the lazy dog again and again and again",
		"0123456789012345678901234567890123456789012345678901234567890123456789"
	};
	char			buf[256];
	char			*ret;
	unsigned long	i;
	unsigned long	j;

	i = 0;
	while (i < sizeof(cases) / sizeof(cases[0]))
	{
		j = 0;
		while (j < sizeof(buf))
		{
			buf[j] = 'X';
			j++;
		}
		buf[sizeof(buf) - 1] = '\0';
		ret = ft_strcpy(buf, cases[i]);
		printf("case %lu: buf=[%s] ret=[%s] same=%d\n",
			i, buf, ret, ret == buf);
		i++;
	}
	return (0);
}
