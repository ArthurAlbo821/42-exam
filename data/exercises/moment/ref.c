#include <stdlib.h>

static int	nb_len(unsigned int n)
{
	int	len;

	len = 1;
	while (n >= 10)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static void	pick_unit(unsigned int duration, unsigned int *value,
		const char **unit)
{
	if (duration >= 2592000)
	{
		*value = duration / 2592000;
		*unit = "month";
	}
	else if (duration >= 86400)
	{
		*value = duration / 86400;
		*unit = "day";
	}
	else if (duration >= 3600)
	{
		*value = duration / 3600;
		*unit = "hour";
	}
	else if (duration >= 60)
	{
		*value = duration / 60;
		*unit = "minute";
	}
	else
	{
		*value = duration;
		*unit = "second";
	}
}

static int	put_nb(char *dst, unsigned int value)
{
	int	len;
	int	i;

	len = nb_len(value);
	i = len - 1;
	while (i >= 0)
	{
		dst[i] = '0' + (value % 10);
		value /= 10;
		i--;
	}
	return (len);
}

static int	put_str(char *dst, const char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	return (i);
}

char	*moment(unsigned int duration)
{
	unsigned int	value;
	const char		*unit;
	char			*res;
	int				i;

	pick_unit(duration, &value, &unit);
	res = malloc(sizeof(char) * (nb_len(value) + 20));
	if (!res)
		return (0);
	i = put_nb(res, value);
	res[i++] = ' ';
	i += put_str(res + i, unit);
	if (value != 1)
		res[i++] = 's';
	i += put_str(res + i, " ago.");
	res[i] = '\0';
	return (res);
}
