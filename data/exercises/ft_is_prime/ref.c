int	ft_is_prime(int nb)
{
	long	i;

	if (nb < 2)
		return (0);
	i = 2;
	while (i * i <= (long)nb)
	{
		if (nb % i == 0)
			return (0);
		i++;
	}
	return (1);
}
