#include <stdio.h>
#include <stddef.h>

size_t	ft_strcspn(const char *s, const char *reject);

static void	test(const char *s, const char *reject)
{
	printf("[%s] / [%s] -> %zu\n", s, reject, ft_strcspn(s, reject));
}

int	main(void)
{
	test("hello world", "h");
	test("hello world", "l");
	test("hello world", "xyz");
	test("hello world", " ");
	test("hello world", "");
	test("", "abc");
	test("", "");
	test("42is-the-answer", "-");
	test("abcdef", "f");
	return (0);
}
