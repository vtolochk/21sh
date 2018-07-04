#include "shell.h"

int		count_sign(char *str, char sign)
{
	int i;
	int sum;

	i = 0;
	sum = 0;
	if (!str || !sign)
		return (0);
	while (str[i])
	{
		if (str[i] == sign)
			sum++;
		i++;
	}
	return (sum);
}