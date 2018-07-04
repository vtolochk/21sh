#include "shell.h"

void substitute_tild(char **str)
{
	char *temp;
	char *for_free;

	if (str && *str && (*str)[0] == '~')
	{
		for_free = *str;
		temp = ft_strdup(get_value_by_name("HOME"));
		*str = ft_strjoin(temp, &(*str)[1]);
		ft_strdel(&for_free);
		ft_strdel(&temp);
	}
}