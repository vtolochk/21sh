/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_paste_actions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtolochk <vtolochk@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 14:31:00 by vtolochk          #+#    #+#             */
/*   Updated: 2018/05/29 14:31:00 by vtolochk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void paste(void)
{
	int i;

	i = 0;
	if (g_data.key[0] == -30 && g_data.key[1] == -120 && g_data.key[2] == -102) // alt-v PASTE BUFFER
	{
		while (g_data.buffer[i])
		{
			insert_char(g_data.buffer[i]);
			i++;
		}
	}
}

void copy(void)
{
	char *string;

	string = NULL;
	if (g_data.key[0] == -50 && g_data.key[1] == -87)  //alt-z COPY BEFORE CURSOR
	{
		ft_bzero(g_data.buffer, sizeof(g_data.buffer));
		string = ft_strsub(g_data.command, 0, g_data.cursor - g_data.prompt_len);
		ft_strcpy(g_data.buffer, string);
	}
	else if (g_data.key[0] == -30 && g_data.key[1] == -119 && g_data.key[2] == -120) //alt-x COPY AFTER CURSOR
	{
		ft_bzero(g_data.buffer, sizeof(g_data.buffer));
		string = ft_strsub(g_data.command, g_data.cursor - g_data.prompt_len, g_data.command_len);
		ft_strcpy(g_data.buffer, string);
	}
	else if (g_data.key[0] == -61 && g_data.key[1] == -89) //alt-c COPY ALL
	{
		ft_bzero(g_data.buffer, sizeof(g_data.buffer));
		ft_strcpy(g_data.buffer, g_data.command);
	}
	ft_strdel(&string);
}

void cut(void)
{
	int i;

	if (g_data.key[0] == -61 && g_data.key[1] == -91) //alt-a CUT BEFORE CURSOR
	{
		i = g_data.cursor - g_data.prompt_len;
		while (g_data.command[i])
		{
			delete_char();
			i++;
		}
	}
	else if (g_data.key[0] == -61 && g_data.key[1] == -97) //alt-s CUT AFTER CURSOR
	{

	}
	else if (g_data.key[0] == -30 && g_data.key[1] == -120 && g_data.key[2] == -126) //alt-d CUT ALL
	{

	}
}

void copy_paste_actions(void)
{
	cut();
	copy();
	paste();
	//dprintf(2, "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n |%d|  |%d|  |%d|  |%d|  |%d|  |%d|  |%d|  |%d| \n", g_data.key[0], g_data.key[1], g_data.key[2], g_data.key[3], g_data.key[4], g_data.key[5], g_data.key[6], g_data.key[7]);
}