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

//void get_y_position(void)
//{
//	char y[3];
//	char buf[8];
//	char *cmd;
//
//	cmd ="\033[6n";
//	write(1, cmd, sizeof(cmd));
//	read (0 ,buf, sizeof(buf));
//	y[0] = buf[2];
//	y[1] = buf[3];
//	y[2] = '\0';
//	g_data.cursor.y = ft_atoi(y);
//}
