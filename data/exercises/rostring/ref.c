#include <unistd.h>

static int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t');
}

static void	ft_putword(char *s, int start, int end)
{
	while (start < end)
	{
		write(1, &s[start], 1);
		start++;
	}
}

int	main(int argc, char **argv)
{
	char	*s;
	int		i;
	int		start;
	int		printed;
	int		first_start;
	int		first_end;

	if (argc != 2)
	{
		write(1, "\n", 1);
		return (0);
	}
	s = argv[1];
	i = 0;
	while (s[i] && ft_isspace(s[i]))
		i++;
	first_start = i;
	while (s[i] && !ft_isspace(s[i]))
		i++;
	first_end = i;
	printed = 0;
	while (s[i])
	{
		while (s[i] && ft_isspace(s[i]))
			i++;
		if (!s[i])
			break ;
		start = i;
		while (s[i] && !ft_isspace(s[i]))
			i++;
		if (printed)
			write(1, " ", 1);
		ft_putword(s, start, i);
		printed = 1;
	}
	if (first_start < first_end)
	{
		if (printed)
			write(1, " ", 1);
		ft_putword(s, first_start, first_end);
	}
	write(1, "\n", 1);
	return (0);
}
