#include <stdio.h>

char	*ft_strupcase(char *str);

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
	printf("case %d: [%s]\n", k, ft_strupcase(buf));
}

int	main(void)
{
	show(0, "hello");
	show(1, "Hello World 42");
	show(2, "ALREADY");
	show(3, "");
	show(4, "a-b_c d!");
	return (0);
}
