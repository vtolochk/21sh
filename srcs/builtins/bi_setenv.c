#include "shell.h"

void			change_list(char *name, char *new_value)
{
	t_env *list;

	list = g_data.environ;
	while (list)
	{
		if (ft_strequ(list->name, name))
		{
			ft_strdel(&list->value);
			list->value = ft_strdup(new_value);
			break ;
		}
		list = list->next;
	}
}

static void add_variable(char *name, char *value)
{
	t_env *list;
	t_env *node;

	list = g_data.environ;
	node = new_node();
	node->name = ft_strdup(name);
	node->value = ft_strdup(value);
	while (list->next)
		list = list->next;
	list->next = node;
}

int bi_setenv(char **argv)
{
	char *name;
	char *new_value;

	if (!(argv[1]) || !(ft_strchr(argv[1], '=')) ||	argv[1][0] == '=' || argv[2] || argv[1][0] != '$' || 
	!(name = ft_strsub(argv[1], 0, ft_strchr(argv[1], '=') - argv[1])) ||
	!(new_value = ft_strsub(argv[1], (ft_strchr(argv[1], '=') - argv[1]) + 1, ft_strlen(argv[1]))))
		ft_putstr_fd("Usage: setenv [$NAME]=[VALUE]\n", 2);
	else
	{
		if (ft_strequ(name, "$PWD") || ft_strequ(name, "$HOME") ||
			ft_strequ(name, "$OLDPWD"))
			ft_printf("This variable cannot be changed.\n");
		else if (get_value_by_name(&name[1]))
		{
			substitute_env_var(&new_value);
			change_list(&name[1], new_value);
		}
		else
		{
			substitute_env_var(&new_value);
			add_variable(&name[1], new_value);
		}	
		ft_strdel(&name);
		ft_strdel(&new_value);
	}
	return (1);
}