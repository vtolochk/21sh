#include "shell.h"

int bi_clear(char **argv)
{
	if (array_len(argv) > 1)
		ft_putstr_fd("clear: too many arguments\n", 2);
	else
		capability("cl");
	return (1);
}