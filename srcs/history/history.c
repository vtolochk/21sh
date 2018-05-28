/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtolochk <vtolochk@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 17:57:00 by vtolochk          #+#    #+#             */
/*   Updated: 2018/05/22 17:57:00 by vtolochk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

#include <stdio.h>

t_history *history_new_node(char *command)
{
	t_history *new_node;

	new_node = (t_history *)malloc(sizeof(t_history));
	new_node->command = ft_strdup(command);
	new_node->next = NULL;
	new_node->prev = NULL;
	return (new_node);
}

void debug_list(void)
{
	t_history *temp = g_data.history_list;
	dprintf(2, "\n*** list ***\n");
	while (temp)
	{
		dprintf(2, "|%s|\n", temp->command);
		temp = temp->next;
	}
	dprintf(2, "\n*** end list ***\n");
}

void history_save(void)
{
	t_history *temp_next;
	t_history *new_node;

	new_node  = g_data.command[0] ? history_new_node(g_data.command) : NULL;
	if (!new_node)
		return ;
	if (g_data.history_list)
	{
		history_go_to_the_first_element();
		temp_next = g_data.history_list->next;
		g_data.history_list->next = new_node;
		new_node->next = temp_next;
		new_node->prev = g_data.history_list;
		if (temp_next)
			temp_next->prev = new_node;
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
}

void history_go_to_the_first_element(void)
{
	if (g_data.history_list)
	{
		while (g_data.history_list->prev)
			g_data.history_list = g_data.history_list->prev;
	}
}



void history_down(void)
{
	if (!g_data.history_list)
		return ;
	if (g_data.history_list->prev)
		g_data.history_list = g_data.history_list->prev;
	clean_screen_after_prompt();
	if (!g_data.history_list->command)
	{
		return;
	}
	ft_putstr_fd(g_data.history_list->command, 1);
	ft_bzero(g_data.command, sizeof(g_data.command));
	ft_strcpy(g_data.command, g_data.history_list->command);
	g_data.cursor += ft_strlen(g_data.history_list->command);
}

void history_up(void)
{
	if (!g_data.history_list)
		return ;
	if (g_data.history_list->next)
		g_data.history_list = g_data.history_list->next;
	clean_screen_after_prompt();
	if (!g_data.history_list->command)
		return;
	ft_putstr_fd(g_data.history_list->command, 1);
	ft_bzero(g_data.command, sizeof(g_data.command));
	ft_strcpy(g_data.command, g_data.history_list->command);
	g_data.cursor += ft_strlen(g_data.history_list->command);
}

void history_actions(void)
{

	capability("im");
	if (ft_strequ(&g_data.key[1], ARROW_UP))
		history_up();
	else if (ft_strequ(&g_data.key[1], ARROW_DOWN))
		history_down();
	else if (g_data.history_list)
	{
		history_go_to_the_first_element();
		ft_strdel(&g_data.history_list->command);
	}
	else
		g_data.history_list = history_new_node(g_data.command);
	debug_list();
	capability("ei");
}

void history_free(void)
{

}