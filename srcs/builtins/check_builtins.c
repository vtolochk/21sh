/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtolochk <vtolochk@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 13:25:00 by vtolochk          #+#    #+#             */
/*   Updated: 2018/06/12 13:25:00 by vtolochk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int check_builtins(char **argv)
{
	if (ft_strequ(argv[0], "echo"))
		return (bi_echo(argv));
	else if (ft_strequ(argv[0], "exit"))
		return (bi_exit(argv));
	else if (ft_strequ(argv[0], "clear"))
		return (bi_clear(argv));
	else if (ft_strequ(argv[0], "env"))
		return (bi_env(argv));
	else if (ft_strequ(argv[0], "history"))
		return (bi_history(argv));
	else if (ft_strequ(argv[0], "pwd"))
		return (bi_pwd(argv));
	else if (ft_strequ(argv[0], "setenv"))
		return (bi_setenv(argv));
//	else if (ft_strequ(argv[0], "cd"))
//		return (bi_cd(argv));
//	else if (ft_strequ(argv[0], "unsetenv"))
//		return (bi_unsetenv(argv, 0));
	return (0);
}
