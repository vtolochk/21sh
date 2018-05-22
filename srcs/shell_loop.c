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
	g_data.rows = 1;
	g_data.command_len = 0;
	g_data.cursor_x = g_data.prompt_len;
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
		signals();
		get_screen_size();
		read(STDIN_FILENO, &g_data.key, sizeof(g_data.key));
		if (g_data.key[0] == ENTER)
		{

			int i = 0;
			while (i++ < g_data.rows)
				write(STDOUT_FILENO, "\n", 1);

			//parse_command();
			ft_printf("|%s|\n", g_data.command);
			execute_command();
			print_prompt();
			annulment();
			continue ;
		}
		else if (g_data.key[0] == TAB)
		{
			//autocomplete
		}
		cursor_actions();
		ft_bzero(&g_data.key[0], sizeof(g_data.key));
	}
}