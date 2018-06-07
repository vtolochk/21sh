/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtolochk <vtolochk@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/30 11:33:00 by vtolochk          #+#    #+#             */
/*   Updated: 2018/05/30 11:33:00 by vtolochk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void var_dump(char **arr)
{
	for (int i = 0; arr[i]; ++i)
		ft_printf("\narr[%i] = \"%s\"", i, arr[i]);
}
void var_dump_arr(char ***arr)
{
	for (int i = 0; arr[i]; i++)
	{
		ft_printf("\nARRAY[%i]:", i);
		var_dump(arr[i]);
		ft_printf("\n");
	}
}

void    loop_pipe(char ***cmd)
{
	int     i;
	int     p[2];
	int     fd_in;

	i = 0;
	fd_in = 0;
	//var_dump_arr(cmd);
	while (cmd[i])
	{
		pipe(p);
		if (fork() == 0)
		{
			dup2(fd_in, 0);
			if (cmd[i + 1] != NULL)
				dup2(p[1], 1);
			close(p[0]);
			execvp(cmd[i][0], cmd[i]);
			exit(0);
		}
		else
		{
			if (!(cmd[i + 1]))
				wait(0);
			close(p[1]);
			fd_in = p[0];
			i++;
		}
	}
}

char ***form_commands(char **splited)
{
	int i;
	int arr_len;
	char ***commands;

	i = 0;
	arr_len = array_len(splited);
	commands = (char ***)malloc(sizeof(char **) * (arr_len + 1));
	commands[arr_len] = NULL;
	while (i < arr_len)
	{
		commands[i] = ft_split_whitespaces(splited[i]);
		i++;
	}
	return (commands);
}

void ft_pipe(char **splited)
{
	char ***temp;
	char ***commands;

	commands = form_commands(splited);
	temp = commands;
	loop_pipe(commands);
	commands = temp;
	while (*commands)
	{
		ft_free_tab((void **)*commands);
		commands++;
	}
	free(temp);
}

void execute_command(char *cmd)
{
	char **splited;

	splited = ft_strsplit(cmd, '|');
	ft_pipe(splited);
	ft_free_tab((void **)splited);
	if (ft_strequ(cmd, "exit") == 1)
		shell_exit();
}