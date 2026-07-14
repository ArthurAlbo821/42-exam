#include <unistd.h>

int	main(int argc, char **argv)
{
	int	i;
	int	n;

	i = 0;
	if (argc == 2)
	{
		while (argv[1][i])
		{
			n = 1;
			if (argv[1][i] >= 'a' && argv[1][i] <= 'z')
				n = argv[1][i] - 'a' + 1;
			if (argv[1][i] >= 'A' && argv[1][i] <= 'Z')
				n = argv[1][i] - 'A' + 1;
			while (n > 0)
			{
				write(1, &argv[1][i], 1);
				n--;
			}
			i++;
		}
	}
	write(1, "\n", 1);
	return (0);
}
