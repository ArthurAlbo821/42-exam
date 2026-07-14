#include <stdio.h>

char	*ft_strpbrk(const char *s1, const char *s2);

static void	test(const char *s1, const char *s2)
{
	char	*res;

	res = ft_strpbrk(s1, s2);
	if (res)
		printf("[%s] / [%s] -> [%s]\n", s1, s2, res);
	else
		printf("[%s] / [%s] -> (null)\n", s1, s2);
}

int	main(void)
{
	test("hello world", "h");
	test("hello world", "ol");
	test("hello world", "d");
	test("hello world", "xyz");
	test("hello world", "");
	test("", "abc");
	test("", "");
	test("42 is the answer", "0123456789");
	test("no digits here", "0123456789");
	return (0);
}
