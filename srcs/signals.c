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
	    || sig_num == SIGKILL || sig_num == SIGQUIT || sig_num == SIGTERM)
		{
			write(1, "\n", 1);
			get_screen_size();
			get_rows();
			annulment();
			print_prompt();
		}
	else if (sig_num == SIGWINCH)
	{
		get_screen_size();
		get_rows();
	}
}

void			signals(void)
{
	signal(SIGWINCH, sig_processing);
	signal(SIGINT, sig_processing);
	signal(SIGSTOP, sig_processing);
	signal(SIGCONT, sig_processing);
	signal(SIGABRT, sig_processing);
	signal(SIGQUIT, sig_processing);
	signal(SIGTSTP, sig_processing);
	signal(SIGKILL, sig_processing);
	signal(SIGTERM, sig_processing);
}

void			child_signals(void)
{
	signal(SIGWINCH, SIG_DFL);
	signal(SIGINT,  SIG_DFL);
	signal(SIGSTOP,  SIG_DFL);
	signal(SIGCONT,  SIG_DFL);
	signal(SIGABRT,  SIG_DFL);
	signal(SIGQUIT,  SIG_DFL);
	signal(SIGTSTP,  SIG_DFL);
	signal(SIGKILL,  SIG_DFL);
	signal(SIGTERM,  SIG_DFL);
}