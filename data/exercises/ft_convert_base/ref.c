#include <stdlib.h>

int	str_len(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	is_ws(char c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}

int	base_ok(char *base)
{
	int	i;
	int	j;

	i = 0;
	while (base[i])
	{
		if (base[i] == '+' || base[i] == '-' || is_ws(base[i]))
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

int	idx_of(char *base, char c)
{
	int	i;

	i = 0;
	while (base[i])
	{
		if (base[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

long	parse(char *nbr, char *base)
{
	int		len;
	int		i;
	int		sign;
	int		idx;
	long	res;

	len = str_len(base);
	i = 0;
	sign = 1;
	res = 0;
	while (is_ws(nbr[i]))
		i++;
	while (nbr[i] == '+' || nbr[i] == '-')
	{
		if (nbr[i] == '-')
			sign = -sign;
		i++;
	}
	idx = idx_of(base, nbr[i]);
	while (idx != -1)
	{
		res = res * len + idx;
		i++;
		idx = idx_of(base, nbr[i]);
	}
	return (res * sign);
}

char	*to_base(long n, char *base)
{
	int		len;
	long	tmp;
	int		cnt;
	int		neg;
	char	*res;

	len = str_len(base);
	neg = (n < 0);
	if (neg)
		n = -n;
	cnt = 1;
	tmp = n;
	while (tmp >= len)
	{
		tmp /= len;
		cnt++;
	}
	res = malloc(cnt + neg + 1);
	if (!res)
		return (0);
	res[cnt + neg] = '\0';
	if (neg)
		res[0] = '-';
	cnt = cnt + neg - 1;
	while (cnt >= neg)
	{
		res[cnt] = base[n % len];
		n /= len;
		cnt--;
	}
	return (res);
}

char	*ft_convert_base(char *nbr, char *base_from, char *base_to)
{
	if (!base_ok(base_from) || !base_ok(base_to))
		return (0);
	return (to_base(parse(nbr, base_from), base_to));
}
