#include <unistd.h>
#include <stdlib.h>

static int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

static int	sign_of(char **s)
{
	int	sign;

	sign = 1;
	if (**s == '-')
	{
		sign = -1;
		(*s)++;
	}
	return (sign);
}

static int	*multiply(char *a, char *b, int la, int lb)
{
	int	*res;
	int	i;
	int	j;

	res = malloc(sizeof(int) * (la + lb));
	if (!res)
		return (0);
	i = 0;
	while (i < la + lb)
		res[i++] = 0;
	i = la - 1;
	while (i >= 0)
	{
		j = lb - 1;
		while (j >= 0)
		{
			res[i + j + 1] += (a[i] - '0') * (b[j] - '0');
			j--;
		}
		i--;
	}
	i = la + lb - 1;
	while (i > 0)
	{
		res[i - 1] += res[i] / 10;
		res[i] %= 10;
		i--;
	}
	return (res);
}

static void	print_result(int *res, int len, int sign)
{
	int		start;
	char	c;

	start = 0;
	while (start < len - 1 && res[start] == 0)
		start++;
	if (!(len - start == 1 && res[start] == 0) && sign < 0)
		write(1, "-", 1);
	while (start < len)
	{
		c = '0' + res[start];
		write(1, &c, 1);
		start++;
	}
	write(1, "\n", 1);
}

int	main(int argc, char **argv)
{
	char	*a;
	char	*b;
	int		sign;
	int		*res;

	if (argc != 3)
	{
		write(1, "\n", 1);
		return (0);
	}
	a = argv[1];
	b = argv[2];
	sign = sign_of(&a) * sign_of(&b);
	res = multiply(a, b, ft_strlen(a), ft_strlen(b));
	if (!res)
		return (1);
	print_result(res, ft_strlen(a) + ft_strlen(b), sign);
	free(res);
	return (0);
}
