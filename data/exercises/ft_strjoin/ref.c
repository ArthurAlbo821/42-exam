#include <stdlib.h>

int	str_len(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strjoin(int size, char **strs, char *sep)
{
	char	*res;
	int		total;
	int		i;
	int		j;
	int		k;

	total = 1;
	i = 0;
	while (i < size)
	{
		total += str_len(strs[i]);
		if (i + 1 < size)
			total += str_len(sep);
		i++;
	}
	res = malloc(total);
	if (!res)
		return (0);
	k = 0;
	i = 0;
	while (i < size)
	{
		j = 0;
		while (strs[i][j])
			res[k++] = strs[i][j++];
		j = 0;
		while (i + 1 < size && sep[j])
			res[k++] = sep[j++];
		i++;
	}
	res[k] = '\0';
	return (res);
}
