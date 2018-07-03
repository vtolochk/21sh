#include "shell.h"

static void print_history(void)
{
	int i;
	t_history *list;

	i = 0;
	list = g_data.history_list;
	while (list->next)
		list = list->next;
	while (list)
	{
		if (list->command)
			ft_printf("%i: %s\n", i++, list->command);
		list = list->prev;
	}
}

int bi_history(char **argv)
{
	if (array_len(argv) > 1)
		ft_putstr_fd("history: too many arguments\n", 2);
	else
		print_history();
	return (1);
}