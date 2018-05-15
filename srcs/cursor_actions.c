/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_actions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtolochk <vtolochk@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/14 11:34:00 by vtolochk          #+#    #+#             */
/*   Updated: 2018/05/14 11:34:00 by vtolochk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void delete_char(void)
{
	char *first_part;
	char *second_part;

	first_part = ft_strsub(g_data.command, 0, g_data.x_cursor - 1);
	second_part = ft_strsub(g_data.command, g_data.x_cursor, g_data.command_len);
	print_capability("le");
	print_capability("dc");
	g_data.x_cursor--;
	g_data.command_len--;
	ft_bzero(g_data.command, 4096);
	ft_strcat(g_data.command, first_part);
	ft_strcat(g_data.command, second_part);
	ft_strdel(&first_part);
	ft_strdel(&second_part);
}

void insert_char(void)
{
	char *first_part;
	char *second_part;
	char *middle_part;

	first_part = ft_strsub(g_data.command, 0, g_data.x_cursor);
	middle_part = ft_strjoin(first_part, g_data.current_char);
	second_part = ft_strsub(g_data.command, g_data.x_cursor, g_data.command_len);
	ft_bzero(g_data.command, 4096);
	ft_strcat(g_data.command, middle_part);
	ft_strcat(g_data.command, second_part);
	g_data.x_cursor++;
	g_data.command_len++;
	ft_strdel(&first_part);
	ft_strdel(&second_part);
	ft_strdel(&middle_part);
}

void cursor_actions(void)
{
	print_capability("im");
	if (ft_strequ(&g_data.current_char[1], ARROW_UP))
		return ; // history up
	else if (ft_strequ(&g_data.current_char[1], ARROW_DOWN))
		return ; // history down
	else if (ft_strequ(&g_data.current_char[1], ARROW_LEFT) && g_data.x_cursor > 0)
	{
		g_data.x_cursor--;
		print_capability("le");
	}
	else if(ft_strequ(&g_data.current_char[1], ARROW_RIGHT) && g_data.x_cursor < g_data.command_len)
	{
		g_data.x_cursor++;
		print_capability("nd");
	}
	else if (g_data.current_char[0] == BACKSPACE && g_data.x_cursor > 0)
		delete_char();
	else if (g_data.current_char[0] != ESC && g_data.current_char[0] != BACKSPACE)
	{
		insert_char();
		// print the whole command
		ft_putstr_fd(g_data.command, 1);
	}
	print_capability("ei");
	ft_bzero(&g_data.current_char[0], 8);
}


