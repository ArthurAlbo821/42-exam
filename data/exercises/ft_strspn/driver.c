#include <stdio.h>
#include <stddef.h>

size_t	ft_strspn(const char *s, const char *accept);

static void	test(const char *s, const char *accept)
{
	printf("[%s] / [%s] -> %zu\n", s, accept, ft_strspn(s, accept));
}

int	main(void)
{
	test("abcabc", "abc");
	test("aaabbb", "a");
	test("hello world", "helo");
	test("xyz", "abc");
	test("hello", "");
	test("", "abc");
	test("", "");
	test("12345abc", "0123456789");
	test("   spaces", " ");
	return (0);
}
