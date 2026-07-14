#include <stdlib.h>

static int	ft_is_sep(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

static int	ft_count_words(char *str)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] && ft_is_sep(str[i]))
			i++;
		if (str[i])
			count++;
		while (str[i] && !ft_is_sep(str[i]))
			i++;
	}
	return (count);
}

static char	*ft_dup_word(char *str, int start, int end)
{
	char	*word;
	int		i;

	word = malloc(sizeof(char) * (end - start + 1));
	if (!word)
		return (NULL);
	i = 0;
	while (start + i < end)
	{
		word[i] = str[start + i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

char	**ft_split(char *str)
{
	char	**tab;
	int		i;
	int		start;
	int		w;

	tab = malloc(sizeof(char *) * (ft_count_words(str) + 1));
	if (!tab)
		return (NULL);
	i = 0;
	w = 0;
	while (str[i])
	{
		while (str[i] && ft_is_sep(str[i]))
			i++;
		start = i;
		while (str[i] && !ft_is_sep(str[i]))
			i++;
		if (i > start)
			tab[w++] = ft_dup_word(str, start, i);
	}
	tab[w] = NULL;
	return (tab);
}
