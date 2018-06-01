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

void move_cursor_right(int *cursor)
{
	if ((*cursor) < g_data.command_len + g_data.prompt_len)
	{
		if (((*cursor) + 1) % g_data.ws_col == 0)
		{
			capability("do");
			capability("cr");
			g_data.line++;
		}
		else
			capability("nd");
		(*cursor)++;
	}
}

void move_cursor_left(int *cursor)
{
	int i;

	i = 0;
	if ((*cursor) > g_data.prompt_len)
	{
		if ((*cursor) % g_data.ws_col == 0)
		{
			capability("up");
			while (i++ < g_data.ws_col)
				capability("nd");
			g_data.line--;
		}
		else
			capability("le");
		(*cursor)--;
	}
}

void move_cursor_up(void)
{
	int i;

	i = 0;
	if (g_data.line > 1)
	{
		while (i++ < g_data.ws_col)
			move_cursor_left(&g_data.cursor);
	}
}

void move_cursor_down(void)
{
	int i;
	int last_line;

	i = 0;
	last_line = g_data.line == ((g_data.command_len + g_data.prompt_len) / g_data.ws_col) + 1;
	if (!last_line)
	{
		while (i++ < g_data.ws_col)
			move_cursor_right(&g_data.cursor);
	}
}