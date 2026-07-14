#include <unistd.h>
#include <stdlib.h>

static int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t');
}

static int	count_words(char *s)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] && ft_isspace(s[i]))
			i++;
		if (s[i] && !ft_isspace(s[i]))
			count++;
		while (s[i] && !ft_isspace(s[i]))
			i++;
	}
	return (count);
}

static char	*dup_word(char *s, int start, int end)
{
	char	*word;
	int		i;

	word = (char *)malloc(sizeof(char) * (end - start + 1));
	if (!word)
		return (0);
	i = 0;
	while (start < end)
	{
		word[i] = s[start];
		start++;
		i++;
	}
	word[i] = '\0';
	return (word);
}

static int	fill_words(char *s, char **words)
{
	int	i;
	int	start;
	int	n;

	i = 0;
	n = 0;
	while (s[i])
	{
		while (s[i] && ft_isspace(s[i]))
			i++;
		if (!s[i])
			break ;
		start = i;
		while (s[i] && !ft_isspace(s[i]))
			i++;
		words[n] = dup_word(s, start, i);
		if (!words[n])
			return (-1);
		n++;
	}
	return (n);
}

static int	word_len(char *s)
{
	int	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

static int	cmp_words(char *a, char *b)
{
	int	la;
	int	lb;
	int	i;

	la = word_len(a);
	lb = word_len(b);
	if (la != lb)
		return (la - lb);
	i = 0;
	while (a[i] && b[i])
	{
		if ((unsigned char)a[i] != (unsigned char)b[i])
			return ((unsigned char)a[i] - (unsigned char)b[i]);
		i++;
	}
	return (0);
}

static void	sort_words(char **words, int n)
{
	int		i;
	char	*tmp;

	i = 0;
	while (i < n - 1)
	{
		if (cmp_words(words[i], words[i + 1]) > 0)
		{
			tmp = words[i];
			words[i] = words[i + 1];
			words[i + 1] = tmp;
			if (i > 0)
				i--;
			else
				i++;
		}
		else
			i++;
	}
}

static void	put_word(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		write(1, &s[i], 1);
		i++;
	}
}

int	main(int argc, char **argv)
{
	char	**words;
	int		n;
	int		i;

	if (argc != 2 || count_words(argv[1]) == 0)
	{
		write(1, "\n", 1);
		return (0);
	}
	n = count_words(argv[1]);
	words = (char **)malloc(sizeof(char *) * n);
	if (!words)
		return (1);
	if (fill_words(argv[1], words) != n)
		return (1);
	sort_words(words, n);
	i = 0;
	while (i < n)
	{
		if (i > 0)
			write(1, " ", 1);
		put_word(words[i]);
		free(words[i]);
		i++;
	}
	write(1, "\n", 1);
	free(words);
	return (0);
}
