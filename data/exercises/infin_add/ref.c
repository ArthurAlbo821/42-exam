#include <unistd.h>
#include <stdlib.h>

static int	ft_strlen(char *s)
{
	int	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

static char	*add_str(char *a, char *b)
{
	char	*res;
	int		la;
	int		lb;
	int		i;
	int		carry;
	int		sum;
	int		max;

	la = ft_strlen(a);
	lb = ft_strlen(b);
	max = la;
	if (lb > max)
		max = lb;
	res = (char *)malloc(sizeof(char) * (max + 2));
	if (!res)
		return (0);
	i = 0;
	carry = 0;
	while (i < max || carry)
	{
		sum = carry;
		if (i < la)
			sum = sum + (a[la - 1 - i] - '0');
		if (i < lb)
			sum = sum + (b[lb - 1 - i] - '0');
		res[i] = (sum % 10) + '0';
		carry = sum / 10;
		i++;
	}
	res[i] = '\0';
	return (res);
}

static void	put_reversed(char *s)
{
	int	i;

	i = ft_strlen(s);
	while (i > 1 && s[i - 1] == '0')
		i--;
	while (i > 0)
	{
		i--;
		write(1, &s[i], 1);
	}
	write(1, "\n", 1);
}

int	main(int argc, char **argv)
{
	char	*res;

	if (argc != 3)
	{
		write(1, "\n", 1);
		return (0);
	}
	res = add_str(argv[1], argv[2]);
	if (!res)
		return (1);
	put_reversed(res);
	free(res);
	return (0);
}
