#include <stdio.h>

char	*ft_strlowcase(char *str);

void	show(int k, char *s)
{
	char	buf[64];
	int		i;

	i = 0;
	while (s[i])
	{
		buf[i] = s[i];
		i++;
	}
	buf[i] = '\0';
	printf("case %d: [%s]\n", k, ft_strlowcase(buf));
}

int	main(void)
{
	show(0, "HELLO");
	show(1, "Hello World 42");
	show(2, "already");
	show(3, "");
	show(4, "A-B_C D!");
	return (0);
}
