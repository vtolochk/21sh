/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cut_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtolochk <vtolochk@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/30 10:13:00 by vtolochk          #+#    #+#             */
/*   Updated: 2018/05/30 10:13:00 by vtolochk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void cut_before_cursor(void)
{
	char *string;

	if (ALT_A)
	{
		ft_bzero(g_data.buffer, sizeof(g_data.buffer));
		string = ft_strsub(g_data.command, 0, g_data.cursor - g_data.prompt_len);
		ft_strcpy(g_data.buffer, string);
		while (g_data.cursor > g_data.prompt_len)
			delete_char();
		ft_strdel(&string);
	}
}

static void cut_after_cursor(void)
{
	int save_curs;
	char *string;

	if (ALT_S)
	{
		ft_bzero(g_data.buffer, sizeof(g_data.buffer));
		string = ft_strsub(g_data.command, g_data.cursor - g_data.prompt_len, g_data.command_len);
		ft_strcpy(g_data.buffer, string);
		save_curs = g_data.cursor;
		while (g_data.cursor < g_data.command_len + g_data.prompt_len)
			move_cursor_right();
		while (g_data.cursor > save_curs)
			delete_char();
		ft_strdel(&string);
	}
}

static void cut_all(void)
{
	if (ALT_D)
	{
		ft_bzero(g_data.buffer, sizeof(g_data.buffer));
		ft_strcpy(g_data.buffer, g_data.command);
		while (g_data.cursor < g_data.command_len + g_data.prompt_len)
			move_cursor_right();
		while (g_data.cursor > g_data.prompt_len)
			delete_char();
	}
}

void cut(void)
{
	cut_all();
	cut_before_cursor();
	cut_after_cursor();
}