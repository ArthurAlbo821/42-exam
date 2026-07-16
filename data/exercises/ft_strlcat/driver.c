#include <stdio.h>

unsigned int	ft_strlcat(char *dest, char *src, unsigned int size);

void	show(int n, char *dest, char *src, unsigned int size)
{
	unsigned int	r;

	r = ft_strlcat(dest, src, size);
	printf("case %d: ret=%u dest=[%s]\n", n, r, dest);
}

int	main(void)
{
	char	d0[64] = "foo";
	char	d1[64] = "foo";
	char	d2[64] = "hello ";
	char	d3[64] = "abc";
	char	d4[64] = "";

	show(0, d0, "bar", 64);
	show(1, d1, "bar", 2);
	show(2, d2, "world", 64);
	show(3, d3, "def", 5);
	show(4, d4, "hello", 64);
	return (0);
}
