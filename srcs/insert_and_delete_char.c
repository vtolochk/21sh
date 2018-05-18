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
	capability("le");
	capability("dc");
	g_data.cursor_x--;
	g_data.command_len--;
}

void insert_char(void)
{
	char *tail;
	char *head;
	char *new_tail;

	capability("sc");
	capability("ce");
	if (g_data.cursor_x % g_data.win_size.ws_col == 0)
	{
		capability("do");
		capability("sc");
		capability("ce");
	}
	tail = ft_strsub(g_data.command, g_data.cursor_x - g_data.prompt_len, g_data.command_len);
	head = ft_strsub(g_data.command, 0, g_data.cursor_x - g_data.prompt_len);
	new_tail = ft_strjoin(&g_data.key[0], tail);
	ft_bzero(g_data.command, 4096);
	ft_strcat(g_data.command, head);
	ft_strcat(g_data.command, new_tail);
	ft_putstr_fd(new_tail, 1);
	capability("rc");
	capability("nd");
	g_data.cursor_x++;
	g_data.command_len++;
	ft_strdel(&tail);
	ft_strdel(&head);
	ft_strdel(&new_tail);
}
