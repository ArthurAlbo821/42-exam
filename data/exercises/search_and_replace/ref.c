#include <unistd.h>

int	main(int argc, char **argv)
{
	int		i;
	char	c;

	i = 0;
	if (argc == 4 && argv[2][0] && !argv[2][1] && argv[3][0] && !argv[3][1])
	{
		while (argv[1][i])
		{
			c = argv[1][i];
			if (c == argv[2][0])
				c = argv[3][0];
			write(1, &c, 1);
			i++;
		}
	}
	write(1, "\n", 1);
	return (0);
}
