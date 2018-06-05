/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtolochk <vtolochk@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/30 11:32:00 by vtolochk          #+#    #+#             */
/*   Updated: 2018/05/30 11:32:00 by vtolochk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

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

int token(char c, char next_c)
{
	if (c == '|')
		return (PIPE);
	else if (c == '>' && next_c == '>')
		return (DOUBLE_RIGHT_ARR);
	else if (c == '<' && next_c == '<')
		return (DOUBLE_LEFT_ARR);
	else if (c == '>')
		return (RIGHT_ARR);
	else if (c == '<')
		return (LEFT_ARR);
	return (0);
}

char **parse_command(void)
{
	int i;
	int j;
	int cmd;
	char **commands;   // NEED TO RELOAD MY ALGORITHM

	i = 0;
	cmd = 0;
	commands = ft_strsplit(g_data.command, ';');
	while (commands[i])
	{
		j = 0;
		while (commands[i][j])
		{
			if ((cmd = token(commands[i][j], commands[i][j + 1])) > 0)
			{
				g_cmd_info[i].cmd_before = ft_strsub(g_data.command, 0, j);
				g_cmd_info[i].token = cmd;
				g_cmd_info[i].cmd_after = ft_strsub(g_data.command, j, g_data.command_len);
				break ;
			}
			j++;
		}
		i++;
	}
	return (commands);
}