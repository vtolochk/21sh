#include "shell.h"

static void remove_node(char *name)
{
	t_env		*list;
	t_env		*temp;

	list = g_data.environ;
	while (list->next)
	{
		if (ft_strequ(list->next->name, name))
		{
			ft_strdel(&list->next->name);
			ft_strdel(&list->next->value);
			temp = list->next;
			list->next = list->next->next;
			free(temp);
			break ;
		}
		list = list->next;
	}
}

int bi_unsetenv(char **argv)
{
	if (!(argv[1]) || argv[2] || argv[1][0] != '$')
		ft_putstr_fd("Usage: unsetenv [$NAME]\n", 2);
	else
	{
		if (!get_value_by_name(&argv[1][1]))
			ft_putstr_fd("Cant find the variable.\n", 2);
		else if (ft_strequ(argv[1], "$PWD") || ft_strequ(argv[1], "$HOME") ||
			ft_strequ(argv[1], "$OLDPWD"))
			ft_printf("This variable cannot be deleted.\n");
		else
			remove_node(&argv[1][1]);
	}
	return (1);
}