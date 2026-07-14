#include <unistd.h>

static int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t');
}

static char	ft_conv(char c, char next)
{
	if (next == '\0' || ft_isspace(next))
	{
		if (c >= 'a' && c <= 'z')
			return (c - 32);
	}
	else if (c >= 'A' && c <= 'Z')
		return (c + 32);
	return (c);
}

int	main(int argc, char **argv)
{
	int		i;
	int		j;
	char	c;

	if (argc < 2)
		write(1, "\n", 1);
	i = 1;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			c = ft_conv(argv[i][j], argv[i][j + 1]);
			write(1, &c, 1);
			j++;
		}
		write(1, "\n", 1);
		i++;
	}
	return (0);
}
