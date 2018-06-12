/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtolochk <vtolochk@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 15:52:00 by vtolochk          #+#    #+#             */
/*   Updated: 2018/06/12 15:52:00 by vtolochk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int bi_exit(char **argv)
{
	if (array_len(argv) > 1)
		ft_putstr_fd("exit: too many arguments\n",2);
	else
		shell_exit();
	return (1);
}