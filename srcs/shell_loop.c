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
	g_data.prompt_len = 8; // temporary; need to change each time
	g_data.cursor = g_data.prompt_len;
	ft_bzero(g_data.command, sizeof(g_data.command));
	ft_bzero(&g_data.key[0], 8);
}

void quoting(void)
{
	char quote;

	while (1)
	{
		quote = check_unclosing();
		if (quote)
			wait_quote(quote);
		else
			break ;
	}
	g_data.command_len = ft_strlen(g_data.command);
}

void shell_loop(void)
{
	int i;
	char **for_free;
	char **commands;

	while (1)
	{
		i = 0;
		get_screen_size();
		get_rows();
		signals();
		read(STDIN_FILENO, &g_data.key, sizeof(g_data.key)); // while read
		if (g_data.key[0] == ENTER)
		{
			write(1, "\n", 1);
			history_actions(WORK);
			quoting();
			commands = ft_strsplit(g_data.command, ';');
			for_free = commands;
			while (commands[i])
				execute_command(commands[i++]);
			ft_free_tab((void **)for_free);
			annulment();
			print_prompt();
			continue ;
		}
		cursor_actions();
		history_actions(WORK);
		copy_paste_actions();
		ft_bzero(&g_data.key[0], sizeof(g_data.key));
	}
}