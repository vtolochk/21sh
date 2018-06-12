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

//void do_builtins(char *str, int *i)
//{
//
//}
//
//void do_binary(char *str, int *i)
//{
//
//}
//
//void do_redirect(char **cmd)
//{
//	int i;
//
//	i = 0;
//	while (cmd[i])
//	{
//		do_builtins(cmd[i], &i);
//		do_binary(cmd[i], &i);
//		i++;
//	}
//
//}

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

char **form_helper(char *str) // continue here please
{
	char *before;
	char *quote_string;
	char *after;
	char *close_quote;
	char *find;
	char **new_arr;
	char **after_quote;

	find = ft_strchr(str, '\'');
	if (!find)
		find = ft_strchr(str, '\"');



	before = ft_strsub(str, 0, find - str);

	close_quote = ft_strchr(++find, );
	printf("\nclose quote: %s\n", close_quote);
	quote_string = ft_strsub(str, find - str, close_quote - find);
	printf("\nquote_string: %s\n", quote_string);
	after = ft_strsub(str, close_quote - str, ft_strlen(str));

	new_arr = ft_split_whitespaces(before);

	new_arr = array_append_str(new_arr, quote_string);

	after_quote = ft_split_whitespaces(after);

	new_arr = array_append_array(new_arr, after_quote);

	var_dump(new_arr);
	exit(0);
	return (new_arr);
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
		if (ft_strchr(splited[i], '\'') || ft_strchr(splited[i], '\"'))
			commands[i] = form_helper(splited[i]);
		else
			commands[i] = ft_split_whitespaces(splited[i]);
		i++;
	}
	return (commands);
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
	char ***temp;
	char ***commands;

	commands = form_commands(splited);
	temp = commands;
	pipe_loop(commands);
	while (*commands)
	{
		ft_free_tab((void **)*commands);
		commands++;
	}
	free(temp);
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