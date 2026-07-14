#include <unistd.h>

static void	ft_putnbr(int n)
{
	char	c;

	if (n >= 10)
		ft_putnbr(n / 10);
	c = n % 10 + '0';
	write(1, &c, 1);
}

static int	ft_is_prime(int n)
{
	int	d;

	if (n < 2)
		return (0);
	d = 2;
	while (d * d <= n)
	{
		if (n % d == 0)
			return (0);
		d++;
	}
	return (1);
}

static int	ft_atoi_pos(char *s)
{
	int	i;
	int	n;

	if (!s[0])
		return (-1);
	i = 0;
	n = 0;
	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (-1);
		n = n * 10 + (s[i] - '0');
		i++;
	}
	return (n);
}

int	main(int argc, char **argv)
{
	int	n;
	int	i;
	int	sum;

	n = -1;
	if (argc == 2)
		n = ft_atoi_pos(argv[1]);
	if (n < 1)
	{
		write(1, "0\n", 2);
		return (0);
	}
	sum = 0;
	i = 2;
	while (i <= n)
	{
		if (ft_is_prime(i))
			sum = sum + i;
		i++;
	}
	ft_putnbr(sum);
	write(1, "\n", 1);
	return (0);
}
