int	ft_sqrt(int nb)
{
	long	i;

	if (nb < 1)
		return (0);
	i = 1;
	while (i * i < (long)nb)
		i++;
	if (i * i == (long)nb)
		return ((int)i);
	return (0);
}
