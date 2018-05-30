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
	if (ALT_V)
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
	if (ALT_Z)
	{
		ft_bzero(g_data.buffer, sizeof(g_data.buffer));
		string = ft_strsub(g_data.command, 0, g_data.cursor - g_data.prompt_len);
		ft_strcpy(g_data.buffer, string);
	}
	else if (ALT_X)
	{
		ft_bzero(g_data.buffer, sizeof(g_data.buffer));
		string = ft_strsub(g_data.command, g_data.cursor - g_data.prompt_len + 1, g_data.command_len);
		ft_strcpy(g_data.buffer, string);
	}
	else if (ALT_C)
	{
		ft_bzero(g_data.buffer, sizeof(g_data.buffer));
		ft_strcpy(g_data.buffer, g_data.command);
	}
	ft_strdel(&string);
}

void copy_paste_actions(void)
{
	cut();
	copy();
	paste();
}