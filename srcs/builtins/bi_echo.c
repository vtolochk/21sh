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
	int last_char;
	int new_line;

	i = 1;
	new_line = 1;
	if (ft_strequ(argv[i], "-n"))
	{
		new_line = 0;
		i++;
	}
	while (argv[i])
	{
		j = 0;
		last_char = ft_strlen(argv[i]);
		while (argv[i][j])
		{
			if (j == 0 && (argv[i][j] == '\'' || argv[i][j] == '\"'))
				j++;
			if (j == last_char && (argv[i][j] == '\'' || argv[i][j] == '\"'))
				break ;
			write(STDOUT_FILENO, &argv[i][j], 1);
			j++;
		}
		i++;
	}
	if (new_line)
		write(STDOUT_FILENO, "\n", 1);
	else
	{
		write(STDOUT_FILENO, "\e[7m", 5);
		write(STDOUT_FILENO, "%", 1);
		write(STDOUT_FILENO, EOC, ft_strlen(EOC));
	}
	return (1);
}
