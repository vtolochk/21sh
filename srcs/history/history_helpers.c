/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtolochk <vtolochk@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 14:06:00 by vtolochk          #+#    #+#             */
/*   Updated: 2018/05/29 14:06:00 by vtolochk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_history *history_new_node(char *command)
{
	t_history *new_node;

	new_node = (t_history *)malloc(sizeof(t_history));
	new_node->command = ft_strdup(command);
	new_node->next = NULL;
	new_node->prev = NULL;
	return (new_node);
}

void save_last_command(char **last_command)
{
	if (!(*last_command))
		*last_command = ft_strdup(g_data.command);
	else
	{
		ft_strdel(last_command);
		*last_command = ft_strdup(g_data.command);
	}
}

void history_go_to_the_first_element(void)
{
	if (g_data.history_list)
	{
		while (g_data.history_list->prev)
			g_data.history_list = g_data.history_list->prev;
	}
}

void history_free(void)
{
	t_history *ptr;

	history_go_to_the_first_element();
	while (g_data.history_list)
	{
		ft_strdel(&g_data.history_list->command);
		ptr = g_data.history_list;
		g_data.history_list = g_data.history_list->next;
		free(ptr);
	}
}

void clean_screen_after_prompt(void)
{
	if (g_data.line > 1)
		capability_n("UP", g_data.line - 1);
	capability("cr");
	capability_n("RI", g_data.prompt_len);
	capability("cd");
	g_data.cursor = g_data.prompt_len;
	g_data.line = 1;
}
