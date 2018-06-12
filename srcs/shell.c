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
	if (set_shell_mode() == FAIL)
		shell_exit();
	print_prompt();
	annulment();
	g_data.environ = copy_env(env);
	g_data.history_list = history_new_node(NULL);
}

void shell_exit(void)
{
	// TODO: free env list
	history_actions(EXIT);
	set_old_mode();
	exit(OK);
}

int				main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	shell_init(env);
	shell_loop();
	shell_exit();
	return (OK);
}
