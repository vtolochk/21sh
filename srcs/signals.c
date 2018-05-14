/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtolochk <vtolochk@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/11 12:23:00 by vtolochk          #+#    #+#             */
/*   Updated: 2018/05/11 12:23:00 by vtolochk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void		sig_processing(int sig_num)
{
	if (sig_num == SIGINT || sig_num == SIGABRT || sig_num == SIGSTOP
	   || sig_num == SIGKILL || sig_num == SIGQUIT)
			write(1, "\n", 1);
}

void			signals(void)
{
	// WINCHANGE
	signal(SIGINT, sig_processing);
	signal(SIGSTOP, sig_processing);
	signal(SIGCONT, sig_processing);
	signal(SIGABRT, sig_processing);
	signal(SIGQUIT, sig_processing);
	signal(SIGTSTP, sig_processing);
	signal(SIGKILL, sig_processing);
}