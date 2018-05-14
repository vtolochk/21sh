/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mods.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtolochk <vtolochk@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/14 09:32:00 by vtolochk          #+#    #+#             */
/*   Updated: 2018/05/14 09:32:00 by vtolochk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	set_shell_mode(void)
{
	if (tgetent(NULL, getenv("TERM")) == -1)
		return (FAIL);
	if (tcgetattr(0, &g_data.tty) == -1)
		return (FAIL);
	g_data.old_tty = g_data.tty;
	g_data.tty.c_lflag &= ~(ECHO | ICANON);
	g_data.tty.c_cc[VMIN] = 1;
	tcsetattr(0, TCSAFLUSH, &g_data.tty);
	return (OK);
}

void	set_old_mode(void)
{
	tcsetattr(0, TCSAFLUSH, &g_data.old_tty);
}