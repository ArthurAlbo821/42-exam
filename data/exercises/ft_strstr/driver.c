#include <stdio.h>

char	*ft_strstr(char *str, char *to_find);

void	show(int n, char *str, char *to_find)
{
	char	*r;

	r = ft_strstr(str, to_find);
	printf("case %d: [%s]\n", n, r ? r : "(null)");
}

int	main(void)
{
	show(0, "hello world", "world");
	show(1, "hello world", "o w");
	show(2, "hello world", "xyz");
	show(3, "hello world", "");
	show(4, "aaabaaac", "aaac");
	show(5, "42school42", "42");
	show(6, "abc", "abcd");
	return (0);
}
