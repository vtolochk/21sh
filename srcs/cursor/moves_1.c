/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtolochk <vtolochk@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 16:23:00 by vtolochk          #+#    #+#             */
/*   Updated: 2018/05/22 16:23:00 by vtolochk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void move_cursor_home(void)
{
	while (g_data.cursor > g_data.prompt_len)
		move_cursor_left(&g_data.cursor);
}

void move_cursor_end(void)
{
	while (g_data.cursor < g_data.command_len + g_data.prompt_len)
		move_cursor_right(&g_data.cursor);
}

void move_cursor_to_the_next_word(void)
{
	int index;

	index = g_data.cursor - g_data.prompt_len;
	while (ft_isprint(g_data.command[index]) && !ft_is_whitespace(g_data.command[index]))
	{
		move_cursor_right(&g_data.cursor);
		index++;
	}
	while (ft_is_whitespace(g_data.command[index]))
	{
		move_cursor_right(&g_data.cursor);
		index++;
	}
}

void move_cursor_to_the_prev_word(void)
{
	int index;

	index = g_data.cursor - g_data.prompt_len - 1;
	while (ft_isprint(g_data.command[index]) && !ft_is_whitespace(g_data.command[index - 1]))
	{
		move_cursor_left(&g_data.cursor);
		index--;
	}
	while (ft_is_whitespace(g_data.command[index]))
	{
		move_cursor_left(&g_data.cursor);
		index--;
	}
	while (ft_isprint(g_data.command[index]) && !ft_is_whitespace(g_data.command[index]))
	{
		move_cursor_left(&g_data.cursor);
		index--;
	}
}