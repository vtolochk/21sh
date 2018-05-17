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

void move_cursor_up(void)
{

}

void move_cursor_down(void)
{

}

void move_cursor_right(void)
{
	if (g_data.cursor_x % (g_data.win_size.ws_col - 2) == 0)
		capability("do");
	else
		capability("nd");
	g_data.cursor_x++;
}

void move_cursor_left(void)
{
	if (g_data.cursor_x % (g_data.win_size.ws_col - 1) == 0)
	{
		capability("up");
		for (int i = 0; i < g_data.cursor_x + g_data.prompt_len; ++i)
			capability("nd");
	}
	else
		capability("le");
	g_data.cursor_x--;
}

void cursor_actions(void)
{
	capability("im");
	if (ft_strequ(&g_data.key[1], ARROW_UP))
		return ; // history up
	else if (ft_strequ(&g_data.key[1], ARROW_DOWN))
		return ; // history down
	else if (ft_strequ(&g_data.key[1], CTRL_UP) && g_data.rows > 0)
		move_cursor_up();
	else if (ft_strequ(&g_data.key[1], CTRL_DOWN) && g_data.rows > 0)
		move_cursor_down();
	else if (ft_strequ(&g_data.key[1], ARROW_LEFT) && g_data.cursor_x > g_data.prompt_len)
		move_cursor_left();
	else if(ft_strequ(&g_data.key[1], ARROW_RIGHT) && g_data.cursor_x < g_data.command_len + g_data.prompt_len)
		move_cursor_right();
	else if (g_data.key[0] == BACKSPACE && g_data.cursor_x > g_data.prompt_len)
		delete_char();
	else if (ft_isprint(g_data.key[0]))
		insert_char();
	capability("ei");
}


