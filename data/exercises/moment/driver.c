#include <stdio.h>
#include <stdlib.h>

char	*moment(unsigned int duration);

static void	test(unsigned int duration)
{
	char	*res;

	res = moment(duration);
	printf("%u -> [%s]\n", duration, res);
	free(res);
}

int	main(void)
{
	test(0);
	test(1);
	test(30);
	test(59);
	test(60);
	test(65);
	test(120);
	test(2400);
	test(3599);
	test(3600);
	test(3735);
	test(7200);
	test(86399);
	test(86400);
	test(172800);
	test(2591999);
	test(2592000);
	test(5184000);
	return (0);
}
