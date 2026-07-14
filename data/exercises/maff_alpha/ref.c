#include <unistd.h>

int	main(void)
{
	char	c;
	char	out;
	int		i;

	c = 'a';
	i = 0;
	while (c <= 'z')
	{
		out = c;
		if (i % 2 == 1)
			out = c - 32;
		write(1, &out, 1);
		c++;
		i++;
	}
	write(1, "\n", 1);
	return (0);
}
