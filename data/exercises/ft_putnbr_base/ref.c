#include <unistd.h>

int	base_ok(char *base)
{
	int	i;
	int	j;

	i = 0;
	while (base[i])
	{
		if (base[i] == '+' || base[i] == '-')
			return (0);
		j = i + 1;
		while (base[j])
		{
			if (base[i] == base[j])
				return (0);
			j++;
		}
		i++;
	}
	return (i >= 2);
}

void	put_rec(long n, char *base, int len)
{
	char	c;

	if (n >= len)
		put_rec(n / len, base, len);
	c = base[n % len];
	write(1, &c, 1);
}

void	ft_putnbr_base(int nbr, char *base)
{
	int		len;
	long	n;

	if (!base_ok(base))
		return ;
	len = 0;
	while (base[len])
		len++;
	n = nbr;
	if (n < 0)
	{
		write(1, "-", 1);
		n = -n;
	}
	put_rec(n, base, len);
}
