#include <stdio.h>

int	ft_atoi_base(const char *str, int str_base);

int	main(void)
{
	const char		*strs[] = {
		"12fdb3", "101010", "-abc", "777", "42",
		"-101", "zz", "7", "ff", "-0"
	};
	int				bases[] = {16, 2, 16, 8, 10, 2, 16, 8, 16, 10};
	unsigned long	i;

	i = 0;
	while (i < sizeof(bases) / sizeof(bases[0]))
	{
		printf("atoi_base(\"%s\", %d) = %d\n",
			strs[i], bases[i], ft_atoi_base(strs[i], bases[i]));
		i++;
	}
	return (0);
}
