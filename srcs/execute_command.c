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

//printf("\nI am a child i = %d\n", i);
//printf("\nI am the parent i = %d\n", i);
//wait(NULL);


void    loop_pipe(char ***cmd)
{
	int   fds[2];
	pid_t pid;
	int   fd_in = 0;
	int i;

	i = 0;
	pid = 0;
	while (cmd[i] != NULL)
	{
		pipe(fds);
		pid = fork();
		if (pid == 0)
		{
			dup2(fd_in, 0); //change the input according to the old one
			if (cmd[i + 1] != NULL)
				dup2(fds[1], 1);
			close(fds[0]);
			execvp(cmd[i][0], cmd[i]);
			exit(0);
		}
		else
		{
			close(fds[1]);
			fd_in = fds[0]; //save the input for the next command
			i++;
		}
	}
	waitpid(pid, 0, 0);
	kill(0, 0);
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