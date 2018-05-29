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

void debug_list(char *last_command)
{
	t_history *temp = g_data.history_list;
	dprintf(2, "\n*** list ***\n");
	while (temp)
	{
		dprintf(2, "|%s|\n", temp->command);
		temp = temp->next;
	}
	dprintf(2, "\ng_data.command: |%s|\n", g_data.command);
	dprintf(2, "last_command: |%s|\n", last_command);
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
	g_data.line = 1;
}

void history_go_to_the_first_element(void)
{
	if (g_data.history_list)
	{
		while (g_data.history_list->prev)
			g_data.history_list = g_data.history_list->prev;
	}
}

void history_down(char *last_command)
{
	if (!g_data.history_list)
		return ;
	if (g_data.history_list->prev)
		g_data.history_list = g_data.history_list->prev;
	clean_screen_after_prompt();
	if (!g_data.history_list->command)
	{
		ft_bzero(g_data.command, sizeof(g_data.command));
		if (last_command)
		{
			ft_putstr_fd(last_command, 1);
			ft_bzero(g_data.command, sizeof(g_data.command));
			ft_strcpy(g_data.command, last_command);
			g_data.cursor += ft_strlen(g_data.command);
			g_data.command_len = ft_strlen(g_data.command);
			g_data.line = (g_data.command_len / g_data.ws_col) + 1;
		}
		return ;
	}
	ft_putstr_fd(g_data.history_list->command, 1);
	ft_bzero(g_data.command, sizeof(g_data.command));
	ft_strcpy(g_data.command, g_data.history_list->command);
	g_data.cursor += ft_strlen(g_data.command);
	g_data.command_len = ft_strlen(g_data.command);
	g_data.line = (g_data.command_len / g_data.ws_col) + 1;
}

void history_up(void)
{
	if (!g_data.history_list)
		return ;
	if (g_data.history_list->next)
		g_data.history_list = g_data.history_list->next;
	clean_screen_after_prompt();
	if (!g_data.history_list->command)
		return ;
	ft_putstr_fd(g_data.history_list->command, 1);
	ft_bzero(g_data.command, sizeof(g_data.command));
	ft_strcpy(g_data.command, g_data.history_list->command);
	g_data.cursor += ft_strlen(g_data.command);
	g_data.command_len = ft_strlen(g_data.command);
	g_data.line = (g_data.command_len / g_data.ws_col) + 1;
}

void history_actions(void)
{
	static char *last_command;

	capability("im");
	if (ft_strequ(&g_data.key[1], ARROW_UP))
		history_up();
	else if (ft_strequ(&g_data.key[1], ARROW_DOWN))
		history_down(last_command);
	else if (g_data.history_list)
	{
		history_go_to_the_first_element();
		save_last_command(&last_command);
		if (g_data.key[0] == ENTER)
		{
			ft_strdel(&last_command);
			history_save();
		}
	}
	debug_list(last_command);
	capability("ei");
}

void history_free(void)
{
//	history_go_to_the_first_element();
//	while (g_data.history_list)
//	{
//		ft_strdel()
//	}
}