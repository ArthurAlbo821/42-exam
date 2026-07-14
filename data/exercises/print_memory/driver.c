#include <stdio.h>
#include <stddef.h>

void	print_memory(const void *addr, size_t size);

int	main(void)
{
	static int	tab[10] = {0, 23, 150, 255, 12, 16, 21, 42};
	static char	full[16] = {'H', 'e', 'l', 'l', 'o', ' ', 'W', 'o',
		'r', 'l', 'd', '!', 'a', 'b', 'c', 'd'};
	static char	small[5] = {'4', '2', '\n', 'A', 0};
	static char	one[1] = {'z'};
	static char	mixed[10] = {'a', 'b', 0, 9, 10, 127, 'X', 32, 'Y', 31};

	printf("--- tab (40 bytes) ---\n");
	fflush(stdout);
	print_memory(tab, sizeof(tab));
	printf("--- full (16 bytes) ---\n");
	fflush(stdout);
	print_memory(full, sizeof(full));
	printf("--- small (5 bytes) ---\n");
	fflush(stdout);
	print_memory(small, sizeof(small));
	printf("--- one (1 byte) ---\n");
	fflush(stdout);
	print_memory(one, sizeof(one));
	printf("--- zero (0 bytes) ---\n");
	fflush(stdout);
	print_memory(one, 0);
	printf("--- mixed (10 bytes) ---\n");
	fflush(stdout);
	print_memory(mixed, sizeof(mixed));
	printf("--- end ---\n");
	return (0);
}
