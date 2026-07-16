#include <stdio.h>

unsigned int	ft_strlcpy(char *dest, char *src, unsigned int size);

void	show(int k, char *src, unsigned int size)
{
	char			dest[64] = "----------------------------------";
	unsigned int	r;

	r = ft_strlcpy(dest, src, size);
	printf("case %d: ret=%u dest=[%s]\n", k, r, dest);
}

int	main(void)
{
	show(0, "hello", 64);
	show(1, "hello", 3);
	show(2, "hello", 0);
	show(3, "hello", 6);
	show(4, "", 64);
	show(5, "42school", 5);
	return (0);
}
