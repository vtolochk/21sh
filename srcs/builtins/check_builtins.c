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

int is_builtin(char **argv)
{
	if (ft_strequ(argv[0], "echo"))
		return (1);
	if (ft_strequ(argv[0], "echo"))
		return (1);
	else if (ft_strequ(argv[0], "exit"))
		return (1);
	else if (ft_strequ(argv[0], "clear"))
		return (1);
	else if (ft_strequ(argv[0], "env"))
		return (1);
	else if (ft_strequ(argv[0], "history"))
		return (1);
	else if (ft_strequ(argv[0], "pwd"))
		return (1);
	else if (ft_strequ(argv[0], "setenv"))
		return (1);
	else if (ft_strequ(argv[0], "unsetenv"))
		return (1);
	else if (ft_strequ(argv[0], "cd"))
		return (1);
	return (0);
}

int check_builtins(char **argv)
{
	if (is_builtin(argv))
	{
		if (is_redirect(argv) && !validate_redirection(argv))
		{	
			remove_redirection_from_cmd(&argv);
			for(int i = 0; i < g_redIter; i++)
			{
				redirect_open(i);
				if (ft_strequ(argv[0], "echo"))
					bi_echo(argv);
				else if (ft_strequ(argv[0], "exit"))
					bi_exit(argv);
				else if (ft_strequ(argv[0], "clear"))
					bi_clear(argv);
				else if (ft_strequ(argv[0], "env"))
					bi_env(argv);
				else if (ft_strequ(argv[0], "history"))
					bi_history(argv);
				else if (ft_strequ(argv[0], "pwd"))
					bi_pwd(argv);
				else if (ft_strequ(argv[0], "setenv"))
					bi_setenv(argv);
				else if (ft_strequ(argv[0], "unsetenv"))
					bi_unsetenv(argv);
				else if (ft_strequ(argv[0], "cd"))
					bi_cd(argv);
				redirect_close(i);
			}
			return (1);
		}
		else
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
				else if (ft_strequ(argv[0], "unsetenv"))
					return (bi_unsetenv(argv));
				else if (ft_strequ(argv[0], "cd"))
					return (bi_cd(argv));
		}
	}
	return (0);
}
