#include <unistd.h>

void	put_solution(int *rows)
{
	char	line[11];
	int		i;

	i = 0;
	while (i < 10)
	{
		line[i] = rows[i] + '0';
		i++;
	}
	line[10] = '\n';
	write(1, line, 11);
}

int	safe(int *rows, int col, int row)
{
	int	i;

	i = 0;
	while (i < col)
	{
		if (rows[i] == row || col - i == row - rows[i]
			|| col - i == rows[i] - row)
			return (0);
		i++;
	}
	return (1);
}

int	solve(int *rows, int col)
{
	int	row;
	int	count;

	if (col == 10)
	{
		put_solution(rows);
		return (1);
	}
	count = 0;
	row = 0;
	while (row < 10)
	{
		if (safe(rows, col, row))
		{
			rows[col] = row;
			count += solve(rows, col + 1);
		}
		row++;
	}
	return (count);
}

int	ft_ten_queens_puzzle(void)
{
	int	rows[10];

	return (solve(rows, 0));
}
