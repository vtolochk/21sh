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

void redirection(char **splited, int index)
{
	ft_printf("\nREDIRECT");
	(void)splited;
	(void)index;
}

char *form_string_before(char **splited, int index)
{
	int i;
	char *before;
	char *temp;

	i = 0;
	before = ft_strnew(0);
	while (i < index)
	{
		temp = before;
		before = ft_strjoin(before, splited[i]);
		ft_strdel(&temp);
		temp = before;
		before = ft_strjoin(before, " ");
		ft_strdel(&temp);
		i++;
	}
	return (before);
}

char *form_string_after(char **splited, int index)
{
	char *temp;
	char *after;

	after = ft_strnew(0);
	while (splited[index] && !(ft_strchr(splited[index], '<') && !(ft_strchr(splited[index], '>') &&
	                                                               !(ft_strchr(splited[index], '|')))))
	{
		temp = after;
		after = ft_strjoin(after, splited[index]);
		ft_strdel(&temp);
		temp = after;
		after = ft_strjoin(after, " ");
		ft_strdel(&temp);
		index++;
	}
	return (after);
}


void	new_process(char *process)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		execve(process, 0, 0);
		exit(0);
	}
	wait(&pid);
}

void ft_pipe(char **splited, int index)
{
	char *before;
	char *after;

	before = form_string_before(splited, index);
	index++;
	after = form_string_after(splited, index);

	int pipefd[2];
	int pid1, pid2;
	char **argv1;
	char **argv2;

	argv1 = ft_split_whitespaces(before);
	argv2 = ft_split_whitespaces(after);

	pipe(pipefd);
	pid1 = fork();
	if (pid1 == 0)
	{
		// Hook stdout up to the write end of the pipe and close the read end of
		// the pipe which is no longer needed by this process.
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[0]);
		execvp(argv1[0], argv1);
		exit(0);
	}
	pid2 = fork();
	if (pid2 == 0)
	{
		// Hook stdin up to the read end of the pipe and close the write end of
		// the pipe which is no longer needed by this process.
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[1]);
		execvp(argv2[0], argv2);
		perror("exec");
		exit(0);
	}
	close(pipefd[0]);
	close(pipefd[1]);
	// Wait for everything to finish and exit.
//	waitpid(pid1);
//	waitpid(pid2);

	ft_strdel(&before);
	ft_strdel(&after);
}

void execute_command(char *cmd)
{
	int i;
	char **splited;

	i = 0;
	splited = ft_split_whitespaces(cmd);
	while (splited[i])
	{
		if (ft_strchr(splited[i], '>') || ft_strchr(splited[i], '<'))
				redirection(splited, i);
		else if (ft_strchr(splited[i], '|'))
				ft_pipe(splited, i);
		i++;
	}
	ft_free_tab((void **)splited);
	//commands
	if (ft_strequ(cmd, "exit") == 1)
		shell_exit();
}