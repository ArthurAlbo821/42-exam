#include <stdlib.h>
#include <stdio.h>

static int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

static int	is_operator(char *tok)
{
	if (tok[0] == '\0' || tok[1] != '\0')
		return (0);
	return (tok[0] == '+' || tok[0] == '-' || tok[0] == '*'
		|| tok[0] == '/' || tok[0] == '%');
}

static int	is_number(char *tok)
{
	int	i;

	i = 0;
	if (tok[0] == '-')
		i = 1;
	if (tok[i] == '\0')
		return (0);
	while (tok[i])
	{
		if (tok[i] < '0' || tok[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

static int	apply(int a, int b, char op)
{
	if (op == '+')
		return (a + b);
	if (op == '-')
		return (a - b);
	if (op == '*')
		return (a * b);
	if (op == '/')
		return (a / b);
	return (a % b);
}

static void	print_error(void)
{
	printf("%s\n", "Error");
}

static int	eval(char *s, int *stack)
{
	char	*tok;
	int		top;
	int		i;
	int		j;

	top = 0;
	i = 0;
	tok = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!tok)
		return (0);
	while (s[i])
	{
		while (s[i] == ' ')
			i++;
		if (!s[i])
			break ;
		j = 0;
		while (s[i] && s[i] != ' ')
			tok[j++] = s[i++];
		tok[j] = '\0';
		if (is_number(tok))
			stack[top++] = atoi(tok);
		else if (is_operator(tok) && top >= 2)
		{
			stack[top - 2] = apply(stack[top - 2], stack[top - 1], tok[0]);
			top--;
		}
		else
			return (free(tok), print_error(), 0);
	}
	free(tok);
	if (top != 1)
		return (print_error(), 0);
	return (printf("%d\n", stack[0]), 0);
}

int	main(int argc, char **argv)
{
	int	*stack;

	if (argc != 2)
	{
		printf("%s\n", "Error");
		return (0);
	}
	stack = malloc(sizeof(int) * (ft_strlen(argv[1]) + 1));
	if (!stack)
		return (0);
	eval(argv[1], stack);
	free(stack);
	return (0);
}
