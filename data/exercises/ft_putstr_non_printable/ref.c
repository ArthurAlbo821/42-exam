#include <unistd.h>

void	ft_putstr_non_printable(char *str)
{
	char	*hex;
	int		i;

	hex = "0123456789abcdef";
	i = 0;
	while (str[i])
	{
		if (str[i] >= 32 && str[i] <= 126)
			write(1, &str[i], 1);
		else
		{
			write(1, "\\", 1);
			write(1, &hex[(unsigned char)str[i] >> 4], 1);
			write(1, &hex[(unsigned char)str[i] & 15], 1);
		}
		i++;
	}
}
