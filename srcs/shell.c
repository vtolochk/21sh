/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtolochk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/08 16:39:23 by vtolochk          #+#    #+#             */
/*   Updated: 2018/05/08 16:44:54 by vtolochk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void shell_init(char **env)
{
	g_data.environ = copy_env(env);
}

void shell_exit(void)
{
	// FREE
}

int				main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	shell_init(env);
	shell_loop();
	shell_exit();
	return (0);
}
