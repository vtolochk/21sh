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
	print_capability("im");
	if (ft_strequ(&g_data.key[1], ARROW_UP))
		return ; // history up
	else if (ft_strequ(&g_data.key[1], ARROW_DOWN))
		return ; // history down
	else if (ft_strequ(&g_data.key[1], ARROW_LEFT) && g_data.cursor_x > 0)
	{
		g_data.cursor_x--;
		print_capability("le");
	}
	else if(ft_strequ(&g_data.key[1], ARROW_RIGHT) && g_data.cursor_x < g_data.command_len)
	{
		g_data.cursor_x++;
		print_capability("nd");
	}
	else if (g_data.key[0] == BACKSPACE && g_data.cursor_x > 0)
		delete_char();
	else if (ft_isprint(g_data.key[0]))
		insert_char();
	print_capability("ei");
	ft_bzero(&g_data.key[0], sizeof(g_data.key));
}


