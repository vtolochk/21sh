#include "shell.h"

void    shell_engine(char ***cmd)
{
	pid_t pid;
	int i;
	char **environ;
	int   pipe_fds[2];
	int fd = 0;
	int   fd_in = 0;
	char *full_path_to_file;

	i = 0;
	environ = list_to_array();
	init_redirect();
	while (cmd[i])
	{
		if (is_redirect(cmd[i]) && !validate_redirection(cmd[i]))
		{
			if (check_builtins(cmd[i]))
			{
				i++;
				continue;
			}
			else if (!g_redirect_info[g_redIter - 1].redirect_to_term && check_binaries(cmd[i], environ))
			{
				i++;
				continue;
			}
			else if (g_redirect_info[g_redIter - 1].redirect_to_term)
			{
				remove_redirection_from_cmd(&cmd[i]);
				pipe(pipe_fds);
					pid = fork();
					if (pid == 0)
					{
						dup2(fd_in, 0);
						close(pipe_fds[0]);
						if (cmd[i + 1] != NULL)
							dup2(pipe_fds[1], g_redirect_info[g_redIter - 1].redirect_to);
						full_path_to_file = get_full_path_to_file(cmd[i]);
						if (full_path_to_file)
							execve(full_path_to_file, cmd[i], environ);
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
		}
		else
		{
			if (check_builtins(cmd[i]))
			{
				i++;
				continue;
			}
			pipe(pipe_fds);
			pid = fork();
			if (pid == 0)
			{
				child_signals();
				if (g_redIter > 0)
				{
					if (!g_redirect_info[g_redIter - 1].redirect_to_term)
						fd = open(g_redirect_info[g_redIter - 1].filename, O_RDONLY);
				}
				if (fd > 0)
					dup2(fd, 0);
				else
					dup2(fd_in, 0);
				close(pipe_fds[0]);
				if (cmd[i + 1] != NULL)
					dup2(pipe_fds[1], 1);
				full_path_to_file = get_full_path_to_file(cmd[i]);
				if (full_path_to_file)
					execve(full_path_to_file, cmd[i], environ);
				ft_strdel(&full_path_to_file);
				exit(0);
			}
			else
			{
				close(pipe_fds[1]);
				if (fd > 0)
					fd = pipe_fds[0];
				else
					fd_in = pipe_fds[0];
				i++;
			}
		}
	}
	destroy_redirect();
	ft_free_tab((void **)environ);
	waitpid(pid, 0, 0);
	kill(0, 0);
}