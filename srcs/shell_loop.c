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

void annulment(void)
{
	g_data.x_cursor = 0;
	g_data.command_len = 0;
	ft_bzero(g_data.command, 4096);
	ft_bzero(&g_data.current_char[0], 8);
}

void execute_command(void)
{
	if (ft_strequ(g_data.command, "exit") == 1)
		shell_exit();
}

void shell_loop(void)
{
	print_prompt();
	while (1)
	{
		signals();
		get_screen_size();
		read(STDIN_FILENO, &g_data.current_char, 8);
		if (g_data.current_char[0] == ENTER)
		{
			write(STDOUT_FILENO, "\n", 1);
			//parse_command();
			execute_command();
			print_prompt();
			annulment();
			continue ;
		}
		else if (g_data.current_char[0] == TAB)
		{
			continue; //autocompl
		}
		cursor_actions();
	}
}