/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtolochk <vtolochk@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/14 10:30:00 by vtolochk          #+#    #+#             */
/*   Updated: 2018/05/14 10:30:00 by vtolochk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	get_screen_size(void)
{
	g_data.ws_col = tgetnum("co");
}

void get_rows(void)
{
	if (g_data.command_len && g_data.ws_col)
		g_data.rows = g_data.command_len / g_data.ws_col;
	g_data.rows++;
}