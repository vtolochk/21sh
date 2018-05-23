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

//void history_up(void)
//{
//	t_history *temp;
//
//	temp = g_data.list;
//	while (temp->next)
//		temp = temp->next;
//
//}
//
//void history_down(void)
//{
//
//}
//
//t_history *history_new_node(void)
//{
//	t_history new_node;
//
//	new_node = (t_history *)malloc(sizeof(t_history));
//	new_node->command = ft_strdup(g_data.command);
//	new_node->next = NULL;
//	new_node->prev = NULL;
//	return (new_node);
//}
//
//void history_push_back(t_history *new_node)
//{
//	t_history *temp;
//
//	temp = g_data.list;
//	if (g_data.list)
//	{
//		while (temp->next)
//			temp = temp->next;
//		temp->next = new_node;
//		new_node->next = NULL;
//		new_node->prev = temp;
//	}
//	else
//		g_data.list = new_node;
//
//}
//
//void history_free(void)
//{
//
//}