#include <unistd.h>

int	is_sep(char c)
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
			if (!is_sep(argv[1][i]))
			{
				if (!first)
					write(1, " ", 1);
				while (argv[1][i] && !is_sep(argv[1][i]))
				{
					write(1, &argv[1][i], 1);
					i++;
				}
				first = 0;
			}
			else
				i++;
		}
	}
	write(1, "\n", 1);
	return (0);
}
