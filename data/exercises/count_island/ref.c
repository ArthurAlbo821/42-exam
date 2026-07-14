#include <unistd.h>
#include <stdlib.h>

static char	*read_all(int *total)
{
	char	*buf;
	char	*tmp;
	int		cap;
	int		len;
	int		r;
	int		i;

	cap = 1024;
	len = 0;
	buf = (char *)malloc(cap);
	if (!buf)
		return (0);
	r = read(0, buf + len, cap - len);
	while (r > 0)
	{
		len += r;
		if (len == cap)
		{
			cap *= 2;
			tmp = (char *)malloc(cap);
			if (!tmp)
				return (free(buf), (char *)0);
			i = 0;
			while (i < len)
			{
				tmp[i] = buf[i];
				i++;
			}
			free(buf);
			buf = tmp;
		}
		r = read(0, buf + len, cap - len);
	}
	*total = len;
	return (buf);
}

static void	fill(char *map, int stride, int rows, int idx, char digit)
{
	int	col;
	int	row;

	if (idx < 0)
		return ;
	if (map[idx] != '#')
		return ;
	col = idx % stride;
	row = idx / stride;
	if (col >= stride - 1 || row >= rows)
		return ;
	map[idx] = digit;
	fill(map, stride, rows, idx + 1, digit);
	fill(map, stride, rows, idx - 1, digit);
	fill(map, stride, rows, idx + stride, digit);
	fill(map, stride, rows, idx - stride, digit);
}

static void	solve(char *map, int total)
{
	int		stride;
	int		rows;
	int		i;
	char	digit;

	stride = 0;
	while (stride < total && map[stride] != '\n')
		stride++;
	if (stride == total)
		return ;
	stride += 1;
	rows = total / stride;
	digit = '0';
	i = 0;
	while (i < total)
	{
		if (map[i] == '#')
		{
			fill(map, stride, rows, i, digit);
			digit++;
		}
		i++;
	}
}

int	main(int argc, char **argv)
{
	char	*map;
	int		total;

	(void)argv;
	if (argc != 1)
	{
		write(1, "\n", 1);
		return (0);
	}
	total = 0;
	map = read_all(&total);
	if (!map)
		return (1);
	solve(map, total);
	if (total > 0)
		write(1, map, total);
	free(map);
	return (0);
}
