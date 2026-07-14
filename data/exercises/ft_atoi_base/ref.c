static int	ft_digit_value(char c, int base)
{
	int	val;

	if (c >= '0' && c <= '9')
		val = c - '0';
	else if (c >= 'a' && c <= 'f')
		val = c - 'a' + 10;
	else
		return (-1);
	if (val >= base)
		return (-1);
	return (val);
}

int	ft_atoi_base(const char *str, int str_base)
{
	int	i;
	int	sign;
	int	result;
	int	val;

	i = 0;
	sign = 1;
	result = 0;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	val = ft_digit_value(str[i], str_base);
	while (val >= 0)
	{
		result = result * str_base + val;
		i++;
		val = ft_digit_value(str[i], str_base);
	}
	return (result * sign);
}
