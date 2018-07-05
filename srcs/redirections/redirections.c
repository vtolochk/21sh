#include "shell.h"

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

void get_info(char *cmd, char *next_cmd)
{
		(void)cmd;
		(void)next_cmd;
		g_redirect_info[g_redIter].filename = "fdsa";
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

int validate_redirection(char **cmd)
{
	int redirect_nb;
	int i;
	int j;

	i = 0;
	j = 0;
	redirect_nb = redirections_nb(cmd);
	printf("nb = %d\n", redirect_nb);
	while (cmd[i])
	{
		if (is_str_redirect(cmd[i]))
		{
			if (is_str_redirect(cmd[i + 1]))
				return (redirection_error());
			if (redirection_regexp(cmd[i], 0))
				return (1);
			get_info(cmd[i], cmd[i + 1]);
			if (!g_redirect_info[g_redIter].filename)
				return (redirection_error());
			else
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
		}
		i++;
	}
	return (0);
}

void redirect_open(void)
{
	g_redirect_info[g_redIter].file_fd = open(g_redirect_info[g_redIter].filename, g_redirect_info[g_redIter].flags, 0666);
	g_redirect_info[g_redIter].stdoutCopy = dup(g_redirect_info[g_redIter].redirect_fd);
	dup2(g_redirect_info[g_redIter].file_fd, g_redirect_info[g_redIter].redirect_fd);
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
	while (i < MAX_REDIRECT)
	{
		g_redirect_info[i].filename = NULL;
		g_redirect_info[i].flags = 0;
		g_redirect_info[i].file_fd = -1;
		g_redirect_info[i].redirect_fd = 1;
		g_redirect_info[i].redirection_direction = 0;
		g_redirect_info[i].stdoutCopy = -1;
		i++;
	}
}

void redirect_close(void)
{
	if (g_redirect_info[g_redIter].stdoutCopy >= 0)
	{
		dup2(g_redirect_info[g_redIter].stdoutCopy, g_redirect_info[g_redIter].redirect_fd);
		close(g_redirect_info[g_redIter].stdoutCopy);
		close(g_redirect_info[g_redIter].file_fd);
	}
}