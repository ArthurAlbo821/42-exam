#include <stdio.h>

static char	ft_lower(char c)
{
	if (c >= 'A' && c <= 'Z')
		return (c + 32);
	return (c);
}

static int	ft_isalpha(char c)
{
	c = ft_lower(c);
	return (c >= 'a' && c <= 'z');
}

static int	ft_count(char *s, char c)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	while (s[i])
	{
		if (ft_lower(s[i]) == c)
			n++;
		i++;
	}
	return (n);
}

static int	ft_seen(char *s, int pos)
{
	int	i;

	i = 0;
	while (i < pos)
	{
		if (ft_lower(s[i]) == ft_lower(s[pos]))
			return (1);
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	int	i;
	int	first;

	first = 1;
	if (argc == 2)
	{
		i = 0;
		while (argv[1][i])
		{
			if (ft_isalpha(argv[1][i]) && !ft_seen(argv[1], i))
			{
				if (!first)
					printf(", ");
				printf("%d%c", ft_count(argv[1], ft_lower(argv[1][i])),
					ft_lower(argv[1][i]));
				first = 0;
			}
			i++;
		}
	}
	printf("\n");
	return (0);
}
