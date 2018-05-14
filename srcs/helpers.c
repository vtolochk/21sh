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

void        print_capability_name(char *name)
{
	tputs(tgetstr(name, NULL), 1, &print_command);
}
