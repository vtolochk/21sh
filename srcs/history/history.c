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

void history_save(void)
{
	t_history *temp;
	t_history *new_node;

	temp = g_data.history_tail;
	new_node  = g_data.command[0] ? history_new_node(g_data.command) : NULL;
	if (!new_node)
		return ;
	if (g_data.history_tail)
	{
		while (temp->prev)
			temp = temp->prev;
		temp->prev = new_node;
		new_node->next = temp;
	}
	else
	{
		g_data.history_tail = new_node;
		g_data.history_current = g_data.history_tail;
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

#include <stdio.h> // delete

void history_up(void)
{
	if (!g_data.history_tail)
		return ;
	clean_screen_after_prompt();
	printf("\nhistory_current.command: %s\n", g_data.history_tail->command); // SEGFAULT ????
	//ft_putstr_fd(g_data.history_current->command, 1);
	if (g_data.history_current->prev)
		g_data.history_current = g_data.history_current->prev;
}

void history_down(void)
{
	if (!g_data.history_tail)
		return ;
	clean_screen_after_prompt();
	ft_putstr_fd(g_data.history_current->command, 1);
	if (g_data.history_current->next)
		g_data.history_current = g_data.history_current->next;
}

void history_actions(void)
{
	capability("im");
	if (ft_strequ(&g_data.key[1], ARROW_UP))
		history_up();
	else if (ft_strequ(&g_data.key[1], ARROW_DOWN))
		history_down();
	capability("ei");
}

void history_free(void)
{

}