#include "shell.h"

int bi_env(char **argv)
{
	if (array_len(argv) > 1)
		ft_putstr_fd("env: too many arguments\n", 2);
	else
		print_env();
	return (1);
}