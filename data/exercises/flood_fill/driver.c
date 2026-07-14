#include <stdio.h>
#include <string.h>

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

void	flood_fill(char **tab, t_point size, t_point begin);

static void	print_map(char **tab, int height)
{
	int	i;

	i = 0;
	while (i < height)
	{
		printf("%s\n", tab[i]);
		i++;
	}
	printf("--\n");
}

static void	run_classic(void)
{
	char		b0[16];
	char		b1[16];
	char		b2[16];
	char		b3[16];
	char		b4[16];
	char		*tab[5];
	t_point		size;
	t_point		begin;

	strcpy(b0, "11111111");
	strcpy(b1, "10001001");
	strcpy(b2, "10010001");
	strcpy(b3, "10110001");
	strcpy(b4, "11100001");
	tab[0] = b0;
	tab[1] = b1;
	tab[2] = b2;
	tab[3] = b3;
	tab[4] = b4;
	size.x = 8;
	size.y = 5;
	begin.x = 2;
	begin.y = 2;
	flood_fill(tab, size, begin);
	print_map(tab, 5);
}

static void	run_border(void)
{
	char		b0[8];
	char		b1[8];
	char		b2[8];
	char		*tab[3];
	t_point		size;
	t_point		begin;

	strcpy(b0, "00100");
	strcpy(b1, "00100");
	strcpy(b2, "00100");
	tab[0] = b0;
	tab[1] = b1;
	tab[2] = b2;
	size.x = 5;
	size.y = 3;
	begin.x = 0;
	begin.y = 0;
	flood_fill(tab, size, begin);
	print_map(tab, 3);
}

static void	run_whole(void)
{
	char		b0[8];
	char		b1[8];
	char		*tab[2];
	t_point		size;
	t_point		begin;

	strcpy(b0, "aaaa");
	strcpy(b1, "aaaa");
	tab[0] = b0;
	tab[1] = b1;
	size.x = 4;
	size.y = 2;
	begin.x = 3;
	begin.y = 1;
	flood_fill(tab, size, begin);
	print_map(tab, 2);
}

static void	run_single(void)
{
	char		b0[8];
	char		b1[8];
	char		b2[8];
	char		*tab[3];
	t_point		size;
	t_point		begin;

	strcpy(b0, "xyx");
	strcpy(b1, "yzy");
	strcpy(b2, "xyx");
	tab[0] = b0;
	tab[1] = b1;
	tab[2] = b2;
	size.x = 3;
	size.y = 3;
	begin.x = 1;
	begin.y = 1;
	flood_fill(tab, size, begin);
	print_map(tab, 3);
}

int	main(void)
{
	run_classic();
	run_border();
	run_whole();
	run_single();
	return (0);
}
