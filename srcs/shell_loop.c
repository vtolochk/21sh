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

void init_buffs(void)
{
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
			init_buffs();
		}
		write(STDOUT_FILENO, &g_data.current_char[0], 1);
		ft_strcat(g_data.command, g_data.current_char);
		cursor_actions();
	}
}