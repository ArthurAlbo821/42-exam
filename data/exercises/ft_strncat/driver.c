#include <stdio.h>

char	*ft_strncat(char *dest, char *src, unsigned int nb);

int	main(void)
{
	char	d0[64] = "foo";
	char	d1[64] = "42 ";
	char	d2[64] = "abc";
	char	d3[64] = "x";
	char	d4[64] = "";

	printf("case 0: [%s]\n", ft_strncat(d0, "barbar", 3));
	printf("case 1: [%s]\n", ft_strncat(d1, "school", 100));
	printf("case 2: [%s]\n", ft_strncat(d2, "def", 0));
	printf("case 3: [%s]\n", ft_strncat(d3, "yyyy", 2));
	printf("case 4: [%s]\n", ft_strncat(d4, "hello", 5));
	return (0);
}
