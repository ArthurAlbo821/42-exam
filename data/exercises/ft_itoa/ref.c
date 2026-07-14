#include <stdlib.h>

static int	ft_numlen(long n)
{
	int	len;

	len = 1;
	if (n < 0)
		len++;
	while (n <= -10 || n >= 10)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int nbr)
{
	long	n;
	int		len;
	char	*str;

	n = nbr;
	len = ft_numlen(n);
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	str[len] = '\0';
	if (n < 0)
	{
		str[0] = '-';
		n = -n;
	}
	if (n == 0)
		str[0] = '0';
	while (n > 0)
	{
		len--;
		str[len] = '0' + n % 10;
		n = n / 10;
	}
	return (str);
}
