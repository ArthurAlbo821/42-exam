#include <unistd.h>
#include <stddef.h>

static char	hex_digit(unsigned int v)
{
	if (v < 10)
		return ('0' + v);
	return ('a' + (v - 10));
}

static int	fill_line(const unsigned char *base, size_t size, size_t off,
		char *line)
{
	size_t	i;
	int		p;

	p = 0;
	i = 0;
	while (i < 16)
	{
		if (off + i < size)
		{
			line[p++] = hex_digit(base[off + i] >> 4);
			line[p++] = hex_digit(base[off + i] & 15);
		}
		else
		{
			line[p++] = ' ';
			line[p++] = ' ';
		}
		if (i % 2 == 1)
			line[p++] = ' ';
		i++;
	}
	i = 0;
	while (i < 16 && off + i < size)
	{
		if (base[off + i] >= 32 && base[off + i] <= 126)
			line[p++] = base[off + i];
		else
			line[p++] = '.';
		i++;
	}
	line[p++] = '\n';
	return (p);
}

void	print_memory(const void *addr, size_t size)
{
	const unsigned char	*base;
	char				line[64];
	size_t				off;
	int					len;

	base = (const unsigned char *)addr;
	off = 0;
	while (off < size)
	{
		len = fill_line(base, size, off, line);
		write(1, line, len);
		off += 16;
	}
}
