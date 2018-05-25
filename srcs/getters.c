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
	ioctl(STDERR_FILENO, TIOCGWINSZ, &g_data.win_size);
}

void get_rows(void)
{
	g_data.rows = g_data.command_len / g_data.win_size.ws_col;
	g_data.rows++;
}