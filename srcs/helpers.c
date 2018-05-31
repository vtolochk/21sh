/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtolochk <vtolochk@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/14 16:32:00 by vtolochk          #+#    #+#             */
/*   Updated: 2018/05/14 16:32:00 by vtolochk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int			print_command(int sign)
{
	write(STDIN_FILENO, &sign, 1);
	return (1);
}

void        capability(char *name)
{
	tputs(tgetstr(name, NULL), 1, &print_command);
}

void        capability_n(char *name, int n)
{
	tputs(tgoto(tgetstr(name, 0), 0, n), 1, &print_command);
}

void clear_line(void)
{
	move_cursor_end();
	while (g_data.cursor > g_data.prompt_len)
		delete_char();
}
