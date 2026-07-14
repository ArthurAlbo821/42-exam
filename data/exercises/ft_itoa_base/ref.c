#include <stdlib.h>

static int	ft_nblen(unsigned int n, unsigned int base, int sign)
{
	int	len;

	len = sign;
	if (n == 0)
		return (len + 1);
	while (n != 0)
	{
		n = n / base;
		len++;
	}
	return (len);
}

char	*ft_itoa_base(int value, int base)
{
	char			*digits;
	unsigned int	n;
	int				sign;
	int				len;
	char			*str;

	digits = "0123456789ABCDEF";
	sign = 0;
	if (base == 10 && value < 0)
	{
		sign = 1;
		n = -(unsigned int)value;
	}
	else
		n = (unsigned int)value;
	len = ft_nblen(n, (unsigned int)base, sign);
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (0);
	str[len] = '\0';
	if (sign)
		str[0] = '-';
	if (n == 0)
		str[len - 1] = '0';
	while (n != 0)
	{
		str[--len] = digits[n % (unsigned int)base];
		n = n / (unsigned int)base;
	}
	return (str);
}
