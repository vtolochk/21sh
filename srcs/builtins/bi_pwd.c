#include "shell.h"

int bi_pwd(char **argv)
{
	if (array_len(argv) > 1)
		ft_putstr_fd("pwd: too many arguments\n", 2);
	else
	{
		ft_printf("%s\n", get_value_by_name("PWD"));
	}
	return (1);
}