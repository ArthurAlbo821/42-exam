#include <unistd.h>
#include <stdlib.h>

static int	find_close(char *code, int i)
{
	int	depth;

	depth = 1;
	while (code[i] && depth > 0)
	{
		i++;
		if (code[i] == '[')
			depth++;
		else if (code[i] == ']')
			depth--;
	}
	return (i);
}

static int	find_open(char *code, int i)
{
	int	depth;

	depth = 1;
	while (i > 0 && depth > 0)
	{
		i--;
		if (code[i] == ']')
			depth++;
		else if (code[i] == '[')
			depth--;
	}
	return (i);
}

static void	run(char *code, char *tape)
{
	int		i;
	int		p;

	i = 0;
	p = 0;
	while (code[i])
	{
		if (code[i] == '>')
			p++;
		else if (code[i] == '<')
			p--;
		else if (code[i] == '+')
			tape[p]++;
		else if (code[i] == '-')
			tape[p]--;
		else if (code[i] == '.')
			write(1, &tape[p], 1);
		else if (code[i] == '[' && tape[p] == 0)
			i = find_close(code, i);
		else if (code[i] == ']' && tape[p] != 0)
			i = find_open(code, i);
		i++;
	}
}

int	main(int argc, char **argv)
{
	char	*tape;
	int		i;

	if (argc != 2)
	{
		write(1, "\n", 1);
		return (0);
	}
	tape = malloc(sizeof(char) * 2048);
	if (!tape)
		return (1);
	i = 0;
	while (i < 2048)
		tape[i++] = 0;
	run(argv[1], tape);
	free(tape);
	return (0);
}
