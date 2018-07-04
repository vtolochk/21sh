/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtolochk <vtolochk@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 13:38:00 by vtolochk          #+#    #+#             */
/*   Updated: 2018/06/12 13:38:00 by vtolochk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int bi_echo(char **argv)
{
	int i;
	int j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		substitute_tild(&argv[i]);
		while (argv[i][j])
		{
			if (argv[i][j] == '\'' || argv[i][j] == '\"')
			{
				j++;
				continue ;
			}
			write(STDOUT_FILENO, &argv[i][j], 1);
			j++;
		}
		write(STDOUT_FILENO, " ", 1);
		i++;
	}
	write(STDOUT_FILENO, "\n", 1);
	return (1);
}
