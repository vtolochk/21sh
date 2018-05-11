/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtolochk <vtolochk@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/11 12:42:00 by vtolochk          #+#    #+#             */
/*   Updated: 2018/05/11 12:42:00 by vtolochk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	set_raw_mode(struct termios *old_tty)
{
	struct termios tty;

	tgetent(NULL, getenv("TERM"));
	tcgetattr(0, &tty);
	*old_tty = tty;
	tty.c_lflag &= ECHO;
	tty.c_lflag &= ICANON;
	//tty.c_lflag &= ECHOCTL;
	tty.c_cc[VMIN] = 1;
	tcsetattr(0, TCSAFLUSH, &tty);
}

int read_command(void)
{
	char key[8];
	//char buf[4096];
	read(0, key, 8);
//	if (ret == 8)
//	{
//
//		return (0);
//	}
	//ft_printf("ret: %d, %s\n", ret, key);
	if (key[0] == 'q')
		return (1);
	if (key[0] == 'p')
		print_env();
	return 0;
}

void shell_loop(void)
{
	struct termios old_tty;
	set_raw_mode(&old_tty);
	while (1)
	{
		signals();
		print_prompt();
		if (read_command() == 1)
			break;
	}
	tcsetattr(0, TCSAFLUSH, &old_tty);
}