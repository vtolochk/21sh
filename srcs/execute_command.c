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

int		is_real_file(char *dir, char *name)
{
	DIR *dir_ptr;
	struct dirent *dir_info;

	if (!(dir_ptr = opendir(dir)))
			return (0);
	while ((dir_info = readdir(dir_ptr)))
	{
		if (ft_strequ(dir_info->d_name, name))
		{
			closedir(dir_ptr);
			return (1);
		}
	}
	return (0);
}

char	*create_full_path(char *dir, char *name)
{
	char *temp;
	char *full_path;

	full_path = ft_strjoin(dir, "/");
	temp = full_path;
	full_path = ft_strjoin(full_path, name);
	ft_strdel(&temp);
	return (full_path);
}

int		is_dir(char *full_path)
{
	DIR *ptr;

	if ((ptr = opendir(full_path)))
		return (1);
	return (0);
}

int	can_execute(char *full_path, char *file)
{
	if (access(full_path, X_OK) == -1)
	{
		ft_putstr_fd("shell: permission denied: ", 2);
		ft_putstr_fd(file, 2);
		ft_putstr_fd("\n", 2);
		return (0);
	}
	else if (is_dir(full_path))
	{
		ft_putstr_fd("shell: ", 2);
		ft_putstr_fd(full_path, 2);
		ft_putstr_fd(" cannot execute [It is a directory]\n", 2);
		return (0);
	}
	return (1);
}

void	get_dir_and_file(char **argv, char **dir, char **file)
{
	char *find;

	find = ft_strrchr(argv[0], '/');
	if (find)
	{
		*dir = ft_strsub(argv[0], 0, find - argv[0]);
		*file = ft_strsub(argv[0], ft_strlen(*dir) + 1, \
		ft_strlen(argv[0]) - ft_strlen(*dir));
	}
	else
	{
		*dir = NULL;
		*file = ft_strdup(argv[0]);
	}
}

char *try_to_find_a_file(char *dir, char *file)
{
	int i;
	char *path;
	char *full_path;
	char **path_names;

	i = 0;
	full_path = NULL;
	if (dir && is_real_file(dir, file))
	{
		full_path = create_full_path(dir, file);
		if (can_execute(full_path, file))
			return (full_path);
	}
	else
	{
		if (!(path = get_value_by_name("PATH")) || !(path_names = ft_strsplit(path, ':')))
			return (NULL);
		while (path_names[i])
		{
			if (is_real_file(path_names[i], file))
			{
				full_path = create_full_path(path_names[i], file);
				break ;
			}
			i++;
		}
		ft_free_tab((void **)path_names);
	}
	return (full_path);
}

char *get_full_path_to_file(char **argv)
{
	char *dir;
	char *file;
	char *full_path;

	full_path = NULL;
	get_dir_and_file(argv, &dir, &file);
	full_path = try_to_find_a_file(dir, file);
	if (!full_path && dir)
	{
		ft_putstr_fd("shell: no such file or directory: ", 2);
		ft_putstr_fd(file, 2);
		ft_putstr_fd("\n", 2);
	}
	else if (!full_path)
	{
		ft_putstr_fd("shell: command not found: ", 2);
		ft_putstr_fd(file, 2);
		ft_putstr_fd("\n", 2);
	}
	ft_strdel(&dir);
	ft_strdel(&file);
	return (full_path);
}

int check_binaries(char **cmd, char **environ)
{
	pid_t	pid;
	char *full_path_to_file;
	full_path_to_file = get_full_path_to_file(cmd);
	if (full_path_to_file)
	{
		if (is_redirect(cmd) && !validate_redirection(cmd))
		{
			remove_redirection_from_cmd(&cmd);
			for(int i = 0; i < g_redIter; i++)
			{
				pid = fork();
				redirect_open(i);
				if (pid == 0)
				{
					execve(full_path_to_file, cmd, environ);
					redirect_close(i);
					exit(0);
				}
				else
				{
					wait(&pid);
					redirect_close(i);
				}
			}
		}
		else
		{
			pid = fork();
			if (pid == 0)
			{
				execve(full_path_to_file, cmd, environ);
				exit(0);
			}
			else
			{
				wait(&pid);
			}
		}
		return (1);
	}
	return (0);
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
		//init_redirect();
		var_dump(cmd[i]);
		if (check_builtins(cmd[i])) //|| check_binaries(cmd[i], environ))
		{
			i++;
			//destroy_redirect();
			continue ;
		}
		printf("funny \n");
		pipe(pipe_fds);
		pid = fork();
		if (pid == 0)
		{
			printf("name: %s\n", g_redirect_info[g_redIter - 1].filename);
			dup2(fd_in, 0);
			close(pipe_fds[0]);
			if (cmd[i + 1] != NULL)
				dup2(pipe_fds[1], 1);
			char *full_path_to_file = get_full_path_to_file(cmd[i]);
			if (full_path_to_file)
			{
				execve(full_path_to_file, cmd[i], environ);
			}
			ft_strdel(&full_path_to_file);
			exit(0);
		}
		else
		{
			close(pipe_fds[1]);
			fd_in = pipe_fds[0];
			i++;
		}
	}
	destroy_redirect();
	ft_free_tab((void **)environ);
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
		commands[i] = smart_whitespaces_split(splited[i]);
		i++;
	}
	return (commands);
}

void pipes_and_redirections(char **splited)
{
	int i;
	char ***commands;

	i = 0;
	commands = form_commands(splited);
	pipe_loop(commands);
	while (commands[i])
		ft_free_tab((void **)commands[i++]);
	free(commands);
}

void execute_command(char *cmd)
{
	char **splited;

	splited = smart_pipe_split(cmd);
	pipes_and_redirections(splited);
	ft_free_tab((void **)splited);
}