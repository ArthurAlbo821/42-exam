#include <unistd.h>

static char	ft_match(char c)
{
	if (c == ')')
		return ('(');
	if (c == ']')
		return ('[');
	if (c == '}')
		return ('{');
	return (0);
}

static int	ft_balanced(char *s)
{
	char	stack[4096];
	int		top;
	int		i;
	char	open;

	top = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == '(' || s[i] == '[' || s[i] == '{')
			stack[top++] = s[i];
		else
		{
			open = ft_match(s[i]);
			if (open)
			{
				if (top == 0 || stack[top - 1] != open)
					return (0);
				top--;
			}
		}
		i++;
	}
	return (top == 0);
}

int	main(int argc, char **argv)
{
	int	i;

	if (argc < 2)
	{
		write(1, "\n", 1);
		return (0);
	}
	i = 1;
	while (i < argc)
	{
		if (ft_balanced(argv[i]))
			write(1, "OK\n", 3);
		else
			write(1, "Error\n", 6);
		i++;
	}
	return (0);
}
