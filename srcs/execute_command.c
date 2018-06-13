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
	write(1, "\n", 1);
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

void    pipe_loop(char ***cmd)
{
	int i;
	pid_t pid;
	int   fd_in;
	int   pipe_fds[2];
	char **environ;

	i = 0;
	pid = 0;
	fd_in = 0;
	environ = list_to_array();
	while (cmd[i] != NULL)
	{
		if (check_builtins(cmd[i]))
		{
			i++;
			continue ;
		}
		pipe(pipe_fds);
		pid = fork();
		if (pid == 0)
		{
			dup2(fd_in, 0);
			close(pipe_fds[0]);
			if (cmd[i + 1] != NULL)
				dup2(pipe_fds[1], 1);
			//execve(cmd[i][0], cmd[i], environ);
			execvp(cmd[i][0], cmd[i]);
			exit(0);
		}
		else
		{
			close(pipe_fds[1]);
			fd_in = pipe_fds[0];
			i++;
		}
	}
	ft_free_tab((void **)environ);
	waitpid(pid, 0, 0);
	kill(0, 0);
}

//void redirect_to_the_file(char **cmd, char *filename, int flags, int redirect_fd)
//{
//	int file_fd;
//
//	file_fd = open(filename, flags, 0666);
//	dup2(file_fd, redirect_fd);
//	//new_process();
//	//execvp(cmd[0], cmd);
//}

void pipes_and_redirections(char **splited)
{
	int i;
	char ***commands;

	i = 0;
	commands = form_commands(splited);
	pipe_loop(commands);
	while (commands[i])
	{
		ft_free_tab((void **)commands[i]);
		i++;
	}
	free(commands);
}

void execute_command(char *cmd)
{
	char *trimed;
	char **splited;

	trimed = ft_strtrim(cmd);
	splited = ft_strsplit(trimed, '|');
	pipes_and_redirections(splited);
	ft_strdel(&trimed);
	ft_free_tab((void **)splited);
}