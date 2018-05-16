/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_and_delete_char.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtolochk <vtolochk@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 18:09:00 by vtolochk          #+#    #+#             */
/*   Updated: 2018/05/16 18:09:00 by vtolochk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void delete_char(void)
{
	char *first_part;
	char *second_part;

	first_part = ft_strsub(g_data.command, 0, g_data.cursor_x - 1);
	second_part = ft_strsub(g_data.command, g_data.cursor_x, g_data.command_len);
	print_capability("le");
	print_capability("dc");
	ft_bzero(g_data.command, 4096);
	ft_strcat(g_data.command, first_part);
	ft_strcat(g_data.command, second_part);
	ft_strdel(&first_part);
	ft_strdel(&second_part);
	g_data.cursor_x--;
	g_data.command_len--;
}

void insert_char(void)
{
	char *first_part;
	char *second_part;
	char *middle_part;

	first_part = ft_strsub(g_data.command, 0, g_data.cursor_x);
	middle_part = ft_strjoin(first_part, g_data.key);
	second_part = ft_strsub(g_data.command, g_data.cursor_x, g_data.command_len);
	ft_bzero(g_data.command, 4096);
	ft_strcat(g_data.command, middle_part);
	ft_strcat(g_data.command, second_part);
	ft_strdel(&first_part);
	ft_strdel(&second_part);
	ft_strdel(&middle_part);
	write(1, &g_data.key[0], 1);
	g_data.cursor_x++;
	g_data.command_len++;
}
