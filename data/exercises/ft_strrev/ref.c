char	*ft_strrev(char *str)
{
	int		i;
	int		len;
	char	tmp;

	len = 0;
	while (str[len])
		len++;
	i = 0;
	while (i < len / 2)
	{
		tmp = str[i];
		str[i] = str[len - 1 - i];
		str[len - 1 - i] = tmp;
		i++;
	}
	return (str);
}
