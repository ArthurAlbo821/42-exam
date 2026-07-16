#include <stdio.h>

void	ft_putstr_non_printable(char *str);

void	show(int k, char *s)
{
	printf("case %d: ", k);
	ft_putstr_non_printable(s);
	printf("\n");
}

int	main(void)
{
	setbuf(stdout, NULL);
	show(0, "Hello\nHow are you?");
	show(1, "plain text 42");
	show(2, "tab\there");
	show(3, "");
	show(4, "\x01\x02\x7f end");
	return (0);
}
