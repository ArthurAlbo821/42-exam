#include <unistd.h>

static int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

static void	expand(char *s, int len, int l, int r, int *best)
{
	while (l >= 0 && r < len && s[l] == s[r])
	{
		l--;
		r++;
	}
	l++;
	if (r - l >= best[1] - best[0])
	{
		best[0] = l;
		best[1] = r;
	}
}

int	main(int argc, char **argv)
{
	int	len;
	int	i;
	int	best[2];

	if (argc != 2)
	{
		write(1, "\n", 1);
		return (0);
	}
	len = ft_strlen(argv[1]);
	best[0] = 0;
	best[1] = 0;
	i = 0;
	while (i < len)
	{
		expand(argv[1], len, i, i, best);
		expand(argv[1], len, i, i + 1, best);
		i++;
	}
	write(1, argv[1] + best[0], best[1] - best[0]);
	write(1, "\n", 1);
	return (0);
}
