#include <unistd.h>

static int	ft_is_space(char c)
{
	return (c == ' ' || c == '\t');
}

int	main(int argc, char **argv)
{
	int	i;
	int	first;

	if (argc == 2)
	{
		i = 0;
		first = 1;
		while (argv[1][i])
		{
			while (argv[1][i] && ft_is_space(argv[1][i]))
				i++;
			if (argv[1][i] && !first)
				write(1, "   ", 3);
			if (argv[1][i])
				first = 0;
			while (argv[1][i] && !ft_is_space(argv[1][i]))
			{
				write(1, &argv[1][i], 1);
				i++;
			}
		}
	}
	write(1, "\n", 1);
	return (0);
}
