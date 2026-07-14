#include <unistd.h>

static int	ft_is_space(char c)
{
	return (c == ' ' || c == '\t');
}

static void	ft_putword(char *str, int start)
{
	while (str[start] && !ft_is_space(str[start]))
	{
		write(1, &str[start], 1);
		start++;
	}
}

int	main(int argc, char **argv)
{
	int	i;
	int	j;
	int	first;

	first = 1;
	if (argc == 2)
	{
		i = 0;
		while (argv[1][i])
			i++;
		while (i > 0)
		{
			i--;
			if (!ft_is_space(argv[1][i]))
			{
				j = i;
				while (j > 0 && !ft_is_space(argv[1][j - 1]))
					j--;
				if (!first)
					write(1, " ", 1);
				ft_putword(argv[1], j);
				first = 0;
				i = j;
			}
		}
	}
	write(1, "\n", 1);
	return (0);
}
