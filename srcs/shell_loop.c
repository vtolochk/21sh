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
	g_data.line = 1;
	g_data.command_len = 0;
	g_data.cursor = g_data.prompt_len;
	ft_bzero(g_data.command, 4096);
	ft_bzero(&g_data.key[0], 8);
}

void execute_command(void)
{
	if (ft_strequ(g_data.command, "exit") == 1)
		shell_exit();
}

void shell_loop(void)
{
	while (1)
	{
		get_screen_size();
		get_rows();
		signals();
		read(STDIN_FILENO, &g_data.key, sizeof(g_data.key));
		if (g_data.key[0] == ENTER)
		{
			history_save();
			//parse_command();
			execute_command();
			annulment();
			print_prompt();
			continue ;
		}
		else if (g_data.key[0] == TAB)
		{
			//autocomplete
		}
		cursor_actions();
		history_actions();
		ft_bzero(&g_data.key[0], sizeof(g_data.key));
	}
}