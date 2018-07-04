#include "shell.h"

void substitute_env_var(char **str)
{
	char *find;
	t_env *list;
	char *temp;
	char *for_free;

	find = ft_strchr(*str, '$');
	if (!find)
		return ;
	find++;
	list = g_data.environ;
	while (list)
	{
		if (ft_strequ(find, list->name))
		{
			for_free = *str;
			temp = ft_strdup(list->value);
			*str = ft_strsub(*str, 0, (find - *str) - 1);
			ft_strdel(&for_free);
			for_free = *str;
			*str = ft_strjoin(*str, temp);
			ft_strdel(&for_free);
			ft_strdel(&temp);
			break ;
		}
		list = list->next;
	}
}