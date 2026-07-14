#include <stdio.h>

char	*ft_strrev(char *str);

int	main(void)
{
	char	s0[] = "Hello";
	char	s1[] = "";
	char	s2[] = "a";
	char	s3[] = "ab";
	char	s4[] = "abcdef";
	char	s5[] = "racecar";
	char	s6[] = "the quick brown fox 42";

	printf("case 0: [%s]\n", ft_strrev(s0));
	printf("case 1: [%s]\n", ft_strrev(s1));
	printf("case 2: [%s]\n", ft_strrev(s2));
	printf("case 3: [%s]\n", ft_strrev(s3));
	printf("case 4: [%s]\n", ft_strrev(s4));
	printf("case 5: [%s]\n", ft_strrev(s5));
	printf("case 6: [%s]\n", ft_strrev(s6));
	printf("in place: [%s]\n", s6);
	return (0);
}
