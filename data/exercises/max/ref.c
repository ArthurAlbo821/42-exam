int	max(int *tab, unsigned int len)
{
	int				best;
	unsigned int	i;

	if (len == 0)
		return (0);
	best = tab[0];
	i = 1;
	while (i < len)
	{
		if (tab[i] > best)
			best = tab[i];
		i++;
	}
	return (best);
}
