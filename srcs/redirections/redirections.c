#include "shell.h"

void print_redirect_info(int i)
{
	printf("FILENAME: |%s|\n", g_redirect_info[i].filename);
	printf("flags: |%i|\n", g_redirect_info[i].flags);
	printf("file_fd: |%i|\n", g_redirect_info[i].file_fd);
	printf("reidrect_from[0]: |%i|\n", g_redirect_info[i].redirect_from[0]);
	printf("reidrect_from[1]: |%i|\n", g_redirect_info[i].redirect_from[1]);
	printf("redirect_to: |%i|\n", g_redirect_info[i].redirect_to);
	printf("redirection_direction: |%i|\n", g_redirect_info[i].redirection_direction);
	printf("redirect_from_copy[0]: |%i|\n", g_redirect_info[i].redirect_from_copy[0]);
	printf("redirect_from_copy[1]: |%i|\n", g_redirect_info[i].redirect_from_copy[1]);
	printf("close: |%i|\n", g_redirect_info[i].close ? 1 : 0);
	printf("redirect to term |%i|\n\n",  g_redirect_info[i].redirect_to_term ? 1 : 0);
}

int fd_is_valid(int fd)
{
	if (fcntl(fd, F_GETFD) == -1)
		return (0);
	return (1);
}

int is_redirect(char **argv)
{
	int i;
	int j;
	char quote;

	i = 0;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] == '\'' || argv[i][j] == '\"')
			{
				quote = argv[i][j];
				j++;
				while (argv[i][j] && argv[i][j] != quote)
					j++;
			}
			else if (argv[i][j] == '>' || argv[i][j] == '<')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int is_str_redirect(char *str)
{
	int i;
	char quote;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			quote = str[i];
			i++;
			while (str[i] && str[i] != quote)
				i++;
		}
		else if (str[i] == '>' || str[i] == '<')
			return (1);
		if (!str[i])
			return (0);
		i++;
	}
	return (0);
}

int get_info(char *cmd, char *next_cmd)
{
	int i;

	i = 0;
	if (ft_isdigit(cmd[i]))
	{
		g_redirect_info[g_redIter].redirect_from[0] = ft_atoi(cmd);
		while (ft_isdigit(cmd[i]))
			i++;
	}
	else if (cmd[i] == '&')
	{
		g_redirect_info[g_redIter].redirect_from[0] = 1;
		g_redirect_info[g_redIter].redirect_from[1] = 2;
		i++;
	}
	if (cmd[i] && cmd[i] == '>' && cmd[i + 1] == '>')
	{
		g_redirect_info[g_redIter].flags = TWO_ARROWS;
		g_redirect_info[g_redIter].redirection_direction = RIGHT_ARR;
	}
	else if (cmd[i] == '<' && cmd[i + 1] == '<')
	{
		g_redirect_info[g_redIter].flags = TWO_ARROWS;
		g_redirect_info[g_redIter].redirection_direction = LEFT_ARR;
	}
	else if (cmd[i] == '>')
	{
		g_redirect_info[g_redIter].flags = ONE_ARROW;
		g_redirect_info[g_redIter].redirection_direction = RIGHT_ARR;
	}
	else if (cmd[i] == '<')
	{
		g_redirect_info[g_redIter].flags = ONE_ARROW;
		g_redirect_info[g_redIter].redirection_direction = LEFT_ARR;
	}
	while (cmd[i] && (cmd[i] == '>' || cmd[i] == '<'))
		i++;
	if (cmd[i])
	{
		if (cmd[i] == '&')
		{
			i++;
			if (cmd[i])
			{
				if (cmd[i] == '-')
				{
					g_redirect_info[g_redIter].close = 1;
					i++;
				}
				else
				{
					g_redirect_info[g_redIter].redirect_to = ft_atoi(&cmd[i]);
					if (!fd_is_valid(g_redirect_info[g_redIter].redirect_to))
					{	
						ft_putstr_fd("shell: bad file descriptor\n", 2);
						return (0);
					}
				}
				while (ft_isdigit(cmd[i]))
				{
					i++;
					g_redirect_info[g_redIter].redirect_to_term = 1;
				}
				if (cmd[i] && !g_redirect_info[g_redIter].redirect_to_term)
					g_redirect_info[g_redIter].filename = ft_strsub(cmd, i, ft_strlen(cmd));
				else if (!g_redirect_info[g_redIter].redirect_to_term)
				{
					g_redirect_info[g_redIter].filename = ft_strdup(next_cmd);
					if (!g_redirect_info[g_redIter].filename)
						g_redirect_info[g_redIter].redirect_to_term = 1;
				}
					
			}
		}
		else
	 		g_redirect_info[g_redIter].filename = ft_strsub(cmd, i, ft_strlen(cmd));
	}
	else
		g_redirect_info[g_redIter].filename = ft_strdup(next_cmd);

	return (1);
}

int redirections_nb(char **cmd)
{
	int i;
	int res;

	i = 0;
	res = 0;
	while (cmd[i])
	{
		if (is_str_redirect(cmd[i]))
		{
			if (is_str_redirect(cmd[i + 1]))
				return (0);
			if (redirection_regexp(cmd[i], 1))
				return (0);
			res++;
		}
		i++;
	}
	return (res);
}

void remove_redirection_from_cmd(char ***cmd)
{
	int i;
	int j;
	//char **temp;
	
	i = 0;
	j = 0;
	while ((*cmd)[i])
	{
		if (is_str_redirect((*cmd)[i]))
		{
			//temp = *cmd;
			*cmd = array_remove_element(*cmd, i);
			//ft_free_tab((void**)temp);
			i = 0;
			continue;
		}
		for (int s = 0; s < g_redIter; s++)
		{
			if (ft_strequ(g_redirect_info[s].filename, (*cmd)[i]))
			{
				//temp = *cmd;
				*cmd = array_remove_element(*cmd, i);
				//ft_free_tab((void**)temp);
				i = 0;
				break;
			}
		}
		i++;
	}
}

int validate_redirection(char **cmd)
{
	int redirect_nb;
	int i;
	int j;

	i = 0;
	j = 0;
	redirect_nb = redirections_nb(cmd);
	while (cmd[i])
	{
		if (is_str_redirect(cmd[i]))
		{
			if (is_str_redirect(cmd[i + 1]))
				return (redirection_error());
			if (redirection_regexp(cmd[i], 0))
				return (1);
			if (!get_info(cmd[i], cmd[i + 1]))
				return (0);
			if (!g_redirect_info[g_redIter].filename && !g_redirect_info[g_redIter].redirect_to_term)
				return (redirection_error());
			else
			{
				if (!g_redirect_info[g_redIter].redirect_to_term)
				{
					if (is_dir(g_redirect_info[g_redIter].filename))
					{
						ft_putstr_fd("shell: is a directory ", 2);
						ft_putstr_fd(g_redirect_info[g_redIter].filename, 2);
						ft_putstr_fd("\n", 2);
						return (1);
					}
					else if (access(g_redirect_info[g_redIter].filename, W_OK) == -1 && is_real_file(get_value_by_name("PWD"), g_redirect_info[g_redIter].filename))
					{
						ft_putstr_fd("shell: permission denied: ", 2);
						ft_putstr_fd(g_redirect_info[g_redIter].filename, 2);
						ft_putstr_fd("\n", 2);
						return (1);
					}
				}
				g_redIter++;
			}
		}
		i++;
	}
	return (0);
}

void redirect_open(int i)
{
	//print_redirect_info(i);
	g_data.redirect_is_open = 1;
	if (!g_redirect_info[i].redirect_to_term)
	{
		g_redirect_info[i].redirect_from_copy[0] = dup(g_redirect_info[i].redirect_from[0]);
		if (g_redirect_info[i].redirect_from[1] > 0)
			g_redirect_info[i].redirect_from_copy[1] = dup(g_redirect_info[i].redirect_from[1]);

		if (g_redirect_info[i].close)
		{
			close(g_redirect_info[i].redirect_from[0]);
			if (g_redirect_info[i].redirect_from[1] > 0)
				close(g_redirect_info[i].redirect_from[1]);
		}
		else
		{
			g_redirect_info[i].file_fd = open(g_redirect_info[i].filename, g_redirect_info[i].flags, 0666);
			dup2(g_redirect_info[i].file_fd, g_redirect_info[i].redirect_from[0]);
			if (g_redirect_info[i].redirect_from[1] > 0)
			{
				dup2(g_redirect_info[i].redirect_from[0], g_redirect_info[i].redirect_from[1]);
				close(g_redirect_info[i].file_fd);
			}
		}	
	}
	else
	{
		g_redirect_info[i].redirect_from_copy[0] = dup(g_redirect_info[i].redirect_from[0]);
		if (g_redirect_info[i].redirect_from[1] > 0)
			g_redirect_info[i].redirect_from_copy[1] = dup(g_redirect_info[i].redirect_from[1]);

		if (g_redirect_info[i].close)
		{
			close(g_redirect_info[i].redirect_from[0]);
			if (g_redirect_info[i].redirect_from[1] > 0)
				close(g_redirect_info[i].redirect_from[1]);
		}
		else
		{
			dup2(g_redirect_info[i].redirect_to, g_redirect_info[i].redirect_from[0]);
			if (g_redirect_info[i].redirect_from[1] > 0)
			{
				dup2(g_redirect_info[i].redirect_from[0], g_redirect_info[i].redirect_from[1]);
				close(g_redirect_info[i].redirect_to);
			}
		}
	}
}

void redirect_close(int i)
{
	//print_redirect_info(i);
	g_data.redirect_is_open = 0;
	if (!g_redirect_info[i].redirect_to_term)
	{
		dup2(g_redirect_info[i].redirect_from_copy[0], g_redirect_info[i].redirect_from[0]);
		close(g_redirect_info[i].redirect_from_copy[0]);
		if (g_redirect_info[i].redirect_from_copy[1] > 0)
		{
			dup2(g_redirect_info[i].redirect_from_copy[1], g_redirect_info[i].redirect_from[1]);
			close(g_redirect_info[i].redirect_from_copy[1]);
		}
		close(g_redirect_info[i].file_fd);
	}
	else
	{
		dup2(g_redirect_info[i].redirect_from_copy[0], g_redirect_info[i].redirect_from[0]);
		close(g_redirect_info[i].redirect_from_copy[0]);
		if (g_redirect_info[i].redirect_from_copy[1] > 0)
		{
			dup2(g_redirect_info[i].redirect_from_copy[1], g_redirect_info[i].redirect_from[1]);
			close(g_redirect_info[i].redirect_from_copy[1]);
		}
		// if (g_redirect_info[i].redirect_to[0] > 2)
		// 	close(g_redirect_info[i].redirect_to); // i dont know :D :) :) :)
	}
}

int redirection_error(void)
{
	ft_putstr_fd("parse error\n", 2);
	return (1);
}

int redirection_regexp(char *str, char silent_mode)
{
	int i;

	i = 0;
	while (str[i] != '>' && str[i] != '<')
	{
		if (!ft_isdigit(str[i]) && str[i] != '&')
			return (silent_mode ? 1 : redirection_error());
		else if ((ft_isdigit(str[i]) && str[i + 1] == '&') || (str[i] == '&' && ft_isdigit(str[i + 1])))
			return (silent_mode ? 1 : redirection_error());
		i++;
	}
	if ((str[i] == '>' && str[i + 1] == '>') || (str[i] == '<' && str[i + 1] == '<'))
	{	
		i++;
		if ((str[i] == '>' && str[i + 1] == '>') || (str[i] == '<' && str[i + 1] == '<'))
			return(silent_mode ? 1 : redirection_error());
		return (0);
	}
	else if ((str[i] == '>' && str[i+1] != '>') || (str[i] == '<' && str[i+1] != '<'))
		return (0);
	return (silent_mode ? 1 : redirection_error());
}

void init_redirect(void)
{
	int i;

	i = 0;
	g_redIter = 0;
	while (i < MAX_REDIRECT)
	{
		g_redirect_info[i].filename = NULL;
		g_redirect_info[i].redirection_direction = -1;
		g_redirect_info[i].flags = -1;
		g_redirect_info[i].file_fd = -1;
		g_redirect_info[i].redirect_from[0] = 1;
		g_redirect_info[i].redirect_from[1] = -1;
		g_redirect_info[i].redirect_to = 1;
		g_redirect_info[i].redirect_from_copy[0] = -1;
		g_redirect_info[i].redirect_from_copy[1] = -1;
		g_redirect_info[i].close = 0;
		g_redirect_info[i].redirect_to_term = 0;
		i++;
	}
}

void destroy_redirect(void)
{
	int i;

	i = 0;
	g_redIter = 0;
	while (i < MAX_REDIRECT)
	{
		if (g_redirect_info[i].filename)
			ft_strdel(&g_redirect_info[i].filename);
		i++;
	}
}