#include <unistd.h>

int	is_sep(char c)
{
	return (c == ' ' || c == '\t');
}

void	str_capitalizer(char *str)
{
	int		i;
	char	c;

	i = 0;
	while (str[i])
	{
		c = str[i];
		if (c >= 'A' && c <= 'Z')
			c = c + 32;
		if ((i == 0 || is_sep(str[i - 1])) && c >= 'a' && c <= 'z')
			c = c - 32;
		write(1, &c, 1);
		i++;
	}
	write(1, "\n", 1);
}

int	main(int argc, char **argv)
{
	int	i;

	if (argc < 2)
		write(1, "\n", 1);
	i = 1;
	while (i < argc)
	{
		str_capitalizer(argv[i]);
		i++;
	}
	return (0);
}
