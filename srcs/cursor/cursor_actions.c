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

void cursor_actions(void)
{
	capability("im");
	if (ft_strequ(&g_data.key[1], CTRL_UP))
		move_cursor_up();
	else if (ft_strequ(&g_data.key[1], CTRL_DOWN))
		move_cursor_down();
	else if (ft_strequ(&g_data.key[1], CTRL_LEFT))
		move_cursor_to_the_prev_word();
	else if(ft_strequ(&g_data.key[1], CTRL_RIGHT))
		move_cursor_to_the_next_word();
	else if (ft_strequ(&g_data.key[1], ARROW_LEFT))
		move_cursor_left();
	else if(ft_strequ(&g_data.key[1], ARROW_RIGHT))
		move_cursor_right();
	else if(ft_strequ(&g_data.key[1], END))
		move_cursor_end();
	else if(ft_strequ(&g_data.key[1], HOME))
		move_cursor_home();
	else if (g_data.key[0] == BACKSPACE)
		delete_char();
	else if (ft_isprint(g_data.key[0]))
		insert_char();
	capability("ei");
}


