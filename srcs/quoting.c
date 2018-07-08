/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quoting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtolochk <vtolochk@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/04 17:07:00 by vtolochk          #+#    #+#             */
/*   Updated: 2018/06/04 17:07:00 by vtolochk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int have_quote(char *str, char quote)
{
	int i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i++] == quote)
			return (1);
	}
	return (0);
}

static void print_qoute_prompt(void)
{
	write(1, "\n", 1);
	ft_putstr_fd("quote > ", 1);
	g_data.prompt_len = 8;
}

static void quote_exit(char **last, char **old)
{
	*last = ft_strjoin(*old, g_data.command);
	annulment();
	ft_strcpy(g_data.command, *last);
	ft_strdel(old);
	ft_strdel(last);
	write(1, "\n", 1);
}

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

void wait_quote(char quote)
{
	char *old;
	char *temp;
	char *last;

	old = ft_strdup(g_data.command);
	annulment();
	ft_putstr_fd("quote > ", 1);
	while (1)
	{
		ft_bzero(g_data.key, sizeof(g_data.key));
		read(STDIN_FILENO, &g_data.key, sizeof(g_data.key));
		if (!have_quote(g_data.command, quote) && g_data.key[0] == ENTER)
		{
			temp = old;
			old  = ft_strjoin(old, g_data.command);
			ft_strdel(&temp);
			temp = old;
			old = ft_strjoin(old, "\n");
			ft_strdel(&temp);
			print_qoute_prompt();
			annulment();
			continue ;
		}
		if (have_quote(g_data.command, quote) && g_data.key[0]== ENTER)
			break ;
		cursor_actions();
	}
	quote_exit(&last, &old);
}