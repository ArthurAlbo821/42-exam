#include <unistd.h>

int	main(int argc, char **argv)
{
	int	i;

	if (argc != 2)
	{
		write(1, "z\n", 2);
		return (0);
	}
	i = 0;
	while (argv[1][i])
	{
		if (argv[1][i] == 'z')
		{
			write(1, "z\n", 2);
			return (0);
		}
		i++;
	}
	write(1, "\n", 1);
	return (0);
}
