#include <stdio.h>
#include <stdlib.h>

char	*ft_strjoin(int size, char **strs, char *sep);

void	show(int n, int size, char **strs, char *sep)
{
	char	*r;

	r = ft_strjoin(size, strs, sep);
	printf("case %d: [%s]\n", n, r);
	free(r);
}

int	main(void)
{
	char	*a[] = {"Hello", "world"};
	char	*b[] = {"a", "b", "c", "d"};
	char	*c[] = {"42"};
	char	*d[] = {"x", "y"};

	show(0, 2, a, " ");
	show(1, 4, b, ", ");
	show(2, 1, c, "-");
	show(3, 0, a, "sep");
	show(4, 2, d, "");
	return (0);
}
