#include <stdio.h>

char	*ft_strrepl(char *str, char c1, char c2);

static void	test(const char *src, char c1, char c2)
{
	char	buf[256];
	int		i;

	i = 0;
	while (src[i])
	{
		buf[i] = src[i];
		i++;
	}
	buf[i] = '\0';
	printf("[%s] ('%c'->'%c') -> [%s]\n", src, c1, c2, ft_strrepl(buf, c1, c2));
}

int	main(void)
{
	test("banana", 'a', 'o');
	test("hello world", 'l', 'L');
	test("mississippi", 's', 'S');
	test("no match here", 'z', 'x');
	test("same", 'a', 'a');
	test("", 'a', 'b');
	test("aaaa", 'a', 'a');
	test("abcabcabc", 'c', '-');
	test("spaces here", ' ', '_');
	return (0);
}
