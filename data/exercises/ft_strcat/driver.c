#include <stdio.h>

char	*ft_strcat(char *dest, char *src);

int	main(void)
{
	char	d0[64] = "";
	char	d1[64] = "foo";
	char	d2[64] = "42 ";
	char	d3[64] = "abc";
	char	d4[64] = "end";

	printf("case 0: [%s]\n", ft_strcat(d0, "hello"));
	printf("case 1: [%s]\n", ft_strcat(d1, "bar"));
	printf("case 2: [%s]\n", ft_strcat(d2, "school"));
	printf("case 3: [%s]\n", ft_strcat(d3, ""));
	printf("case 4: [%s]\n", ft_strcat(d4, " of the world"));
	return (0);
}
