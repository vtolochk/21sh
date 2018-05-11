/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtolochk <vtolochk@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/11 11:45:00 by vtolochk          #+#    #+#             */
/*   Updated: 2018/05/11 11:45:00 by vtolochk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int		get_index(char *str, char c)
{
	int i;

	i = 0;
	if (!str)
		return (-1);
	if (str[0] == '\0')
		return (-1);
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

static t_env	*new_node(void)
{
	t_env *node;

	node = (t_env *)malloc(sizeof(t_env));
	node->name = NULL;
	node->value = NULL;
	node->next = NULL;
	return (node);
}

void print_env(void)
{
	t_env *lst;

	lst = g_data.environ;
	while (lst)
	{
		ft_putstr_fd(lst->name, 1);
		write(1, "=", 1);
		ft_putstr_fd(lst->value, 1);
		write(1, "\n", 1);
		lst = lst->next;
	}
}

t_env		*copy_env(char **env)
{
	int			i;
	int			index;
	t_env       *list;
	t_env       *head;

	i = 0;
	list = new_node();
	head = list;
	while (env[i])
	{
		index = get_index(env[i], '=');
		if (index == -1)
			break ;
		list->name = ft_strsub(env[i], 0, index++);
		list->value = ft_strsub(env[i], index, ft_strlen(env[i]) - index);
		if (!env[++i])
			break ;
		list->next = new_node();
		list = list->next;
	}
	return (head);
}