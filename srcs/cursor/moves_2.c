/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtolochk <vtolochk@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 16:23:00 by vtolochk          #+#    #+#             */
/*   Updated: 2018/05/22 16:23:00 by vtolochk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void move_cursor_right(void)
{
	if (g_data.cursor < g_data.command_len + g_data.prompt_len)
	{
		if ((g_data.cursor + 1) % g_data.win_size.ws_col == 0)
		{
			capability("do");
			capability("cr");
			g_data.line++;
		}
		else
			capability("nd");
		g_data.cursor++;
	}
}

void move_cursor_left(void)
{
	int i;

	i = 0;
	if (g_data.cursor > g_data.prompt_len)
	{
		if (g_data.cursor % g_data.win_size.ws_col == 0)
		{
			capability("up");
			while (i++ < g_data.win_size.ws_col)
				capability("nd");
			g_data.line--;
		}
		else
			capability("le");
		g_data.cursor--;
	}
}

void move_cursor_up(void)
{
	int i;

	i = 0;
	if (g_data.line > 1)
	{
		while (i++ < g_data.win_size.ws_col)
			move_cursor_left();
	}
}

void move_cursor_down(void)
{
	int i;
	int last_line;

	i = 0;
	last_line = g_data.line == ((g_data.command_len + g_data.prompt_len) / g_data.win_size.ws_col) + 1;
	if (!last_line)
	{
		while (i++ < g_data.win_size.ws_col)
			move_cursor_right();
	}
}