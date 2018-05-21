/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_and_delete_char.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtolochk <vtolochk@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 18:09:00 by vtolochk          #+#    #+#             */
/*   Updated: 2018/05/16 18:09:00 by vtolochk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void delete_char(void)
{
	char *first_part;
	char *second_part;

	first_part = ft_strsub(g_data.command, 0, g_data.cursor_x - g_data.prompt_len - 1);
	second_part = ft_strsub(g_data.command, g_data.cursor_x - g_data.prompt_len, g_data.command_len);
	ft_bzero(g_data.command, 4096);
	ft_strcat(g_data.command, first_part);
	ft_strcat(g_data.command, second_part);
	ft_strdel(&first_part);
	ft_strdel(&second_part);
	g_data.command_len--;


	capability("dc");
	move_cursor_left();
}


void insert_char(void)
{
	char *tail;
	char *head;
	char *new_tail;

	capability("sc");

	tail = ft_strsub(g_data.command, g_data.cursor_x - g_data.prompt_len, g_data.command_len);
	head = ft_strsub(g_data.command, 0, g_data.cursor_x - g_data.prompt_len);
	new_tail = ft_strjoin(&g_data.key[0], tail);
	ft_bzero(g_data.command, 4096);
	ft_strcat(g_data.command, head);
	ft_strcat(g_data.command, new_tail);

	capability("ce");
	capability("do");
	capability("cr");
	capability("cd");
	capability("rc");
	capability("sc");

	ft_putstr_fd(new_tail, 1);
	capability("rc");
	move_cursor_right();

//	if (g_data.key[0] == 'w')
//	{
//		ft_printf("x:|%d|", g_data.cursor_x);
//	}
	ft_strdel(&tail);
	ft_strdel(&head);
	ft_strdel(&new_tail);
	g_data.command_len++;
}
