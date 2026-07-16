#include <stdio.h>

char	*ft_strncpy(char *dest, char *src, unsigned int n);

void	show(int k, char *src, unsigned int n)
{
	char	dest[32] = "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX";

	ft_strncpy(dest, src, n);
	dest[n] = '\0';
	printf("case %d: [%s]\n", k, dest);
}

int	main(void)
{
	show(0, "hello", 3);
	show(1, "hello", 5);
	show(2, "hi", 5);
	show(3, "", 4);
	show(4, "abcdef", 0);
	show(5, "42school", 8);
	return (0);
}
