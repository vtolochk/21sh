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
	char *tail;
	char *head;

	if (g_data.cursor > g_data.prompt_len)
	{
		tail = ft_strsub(g_data.command, g_data.cursor - g_data.prompt_len, g_data.command_len);
		head = ft_strsub(g_data.command, 0, (g_data.cursor - g_data.prompt_len) - 1);
		ft_bzero(g_data.command, 4096);
		ft_strcat(g_data.command, head);
		ft_strcat(g_data.command, tail);
		g_data.command_len--;
		move_cursor_left(&g_data.cursor);
		capability("cd");
		ft_putstr_fd(tail, 1);
		if (ft_strlen(tail) > 0)
			capability_n("LE", ft_strlen(tail));
		ft_strdel(&tail);
		ft_strdel(&head);
	}
}

void insert_char(char c)
{
	char *tail;
	char *head;
	char *new_tail;
	char new_char[8];

	ft_bzero(new_char, sizeof(new_char));
	new_char[0] = c;
	tail = ft_strsub(g_data.command, g_data.cursor - g_data.prompt_len, g_data.command_len);
	head = ft_strsub(g_data.command, 0, g_data.cursor - g_data.prompt_len);
	new_tail = ft_strjoin(&new_char[0], tail);
	ft_bzero(g_data.command, 4096);
	ft_strcat(g_data.command, head);
	ft_strcat(g_data.command, new_tail);
	g_data.command_len++;
	capability("cd");
	ft_putstr_fd(new_tail, 1);
	capability_n("LE", ft_strlen(new_tail));
	move_cursor_right(&g_data.cursor);
	ft_strdel(&tail);
	ft_strdel(&head);
	ft_strdel(&new_tail);
}
