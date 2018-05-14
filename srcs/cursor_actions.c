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

void get_cursor_position(int *x, int *y)
{
	*x = 0;
	*y = 0;
}

void cursor_actions(void)
{
	int x;
	int y;
	int com_len = ft_strlen(g_data.command);
	get_cursor_position(&x, &y);
	print_capability_name("im");
	if (ft_strequ(&g_data.current_char[1], ARROW_UP))
		return ;
	if (ft_strequ(&g_data.current_char[1], ARROW_DOWN))
		return ;
	if (ft_strequ(&g_data.current_char[1], ARROW_LEFT))
	{
		print_capability_name("le");
	}
	if (ft_strequ(&g_data.current_char[1], ARROW_RIGHT))
	{
		print_capability_name("nd");
	}
	if (g_data.current_char[0] == BACKSPACE)
	{
		tputs(tgetstr("bs", NULL), 1, &print_command);
	}
	print_capability_name("ei");
	ft_bzero(&g_data.current_char[0], 8);
}


