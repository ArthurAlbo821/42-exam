#include <unistd.h>

static int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

static int	match_at(char *hay, char *needle, int start, int len)
{
	int	k;

	k = 0;
	while (k < len)
	{
		if (needle[start + k] != hay[k])
			return (0);
		k++;
	}
	return (1);
}

static int	is_substr(char *hay, char *needle, int start, int len)
{
	int	hlen;
	int	i;

	hlen = ft_strlen(hay);
	i = 0;
	while (i + len <= hlen)
	{
		if (match_at(hay + i, needle, start, len))
			return (1);
		i++;
	}
	return (0);
}

static int	in_all(char **argv, int argc, int start, int len)
{
	int	a;

	a = 2;
	while (a < argc)
	{
		if (!is_substr(argv[a], argv[1], start, len))
			return (0);
		a++;
	}
	return (1);
}

int	main(int argc, char **argv)
{
	int	first_len;
	int	len;
	int	start;

	if (argc < 2)
	{
		write(1, "\n", 1);
		return (0);
	}
	first_len = ft_strlen(argv[1]);
	len = first_len;
	while (len > 0)
	{
		start = 0;
		while (start + len <= first_len)
		{
			if (in_all(argv, argc, start, len))
			{
				write(1, argv[1] + start, len);
				write(1, "\n", 1);
				return (0);
			}
			start++;
		}
		len--;
	}
	write(1, "\n", 1);
	return (0);
}
