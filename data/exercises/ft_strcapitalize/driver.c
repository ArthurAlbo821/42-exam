#include <stdio.h>

char	*ft_strcapitalize(char *str);

void	show(int k, char *s)
{
	char	buf[128];
	int		i;

	i = 0;
	while (s[i])
	{
		buf[i] = s[i];
		i++;
	}
	buf[i] = '\0';
	printf("case %d: [%s]\n", k, ft_strcapitalize(buf));
}

int	main(void)
{
	show(0, "hi, how are you? 42words forty-two; fifty+and+one");
	show(1, "HELLO WORLD");
	show(2, "salut");
	show(3, "");
	show(4, "a1b2 c3D4");
	return (0);
}
