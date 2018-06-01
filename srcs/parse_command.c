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

char check_unclosing(void)
{
	int i;

	i = 0;
	while (g_data.command[i])
	{
		if (g_data.command[i] == '\'')
		{
			i++;
			while(g_data.command[i] && g_data.command[i] != '\'')
				i++;
			if (!g_data.command[i])
				return ('\'');
		}
		if (g_data.command[i] == '\"')
		{
			i++;
			while(g_data.command[i] && g_data.command[i] != '\"')
				i++;
			if (!g_data.command[i])
				return ('\"');
		}
		i++;
	}
	return (0);
}

int have_quote(char *str, char quote)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i++] == quote)
			return (1);
	}
	return (0);
}

void wait_quote(char quote)
{
	char key[8];
	char add[2048];

	ft_bzero(add, sizeof(add));
	g_data.cursor = 0;
	while (1)
	{
		ft_bzero(key, sizeof(key));
		read(STDIN_FILENO, &key, sizeof(key));
		write(1, key, 1);
		if (!have_quote(add, quote) && key[0] == ENTER)
		{
			key[0] = '\\';
			key[1] = 'n';
		}
		if (have_quote(add, quote) && key[0]== ENTER)
			break ;
		ft_strcat(add, key);
	}
	ft_strcat(g_data.command, add);
}

void quoting(void)
{
	char quote;

	quote = check_unclosing();
	if (quote)
		wait_quote(quote);
}

void parse_command(void)
{
	quoting();
}