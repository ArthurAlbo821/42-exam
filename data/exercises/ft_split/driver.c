#include <stdio.h>
#include <stdlib.h>

char	**ft_split(char *str);

static void	run_case(int n, char *str)
{
	char	**tab;
	int		i;

	tab = ft_split(str);
	printf("case %d:\n", n);
	i = 0;
	while (tab[i])
	{
		printf("  [%s]\n", tab[i]);
		free(tab[i]);
		i++;
	}
	printf("  (null)\n");
	free(tab);
}

int	main(void)
{
	char	*cases[] = {
		"the quick brown fox",
		"multiple   spaces    between",
		"   leading and trailing   ",
		"",
		"   \t \n  ",
		"single",
		"tabs\tand\nnewlines\there"
	};
	int		i;

	i = 0;
	while (i < 7)
	{
		run_case(i, cases[i]);
		i++;
	}
	return (0);
}
