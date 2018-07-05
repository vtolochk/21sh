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

void get_info(char *cmd, t_redirect **info)
{
	(*info)->filename = "kaka";
	printf("get info cmd=|%s|, info_filename |%s|", cmd, (*info)->filename);			
}


int validate_redirection(char **cmd, t_redirect *info)
{
	int i;

	i = 0;
	while (cmd[i])
	{
		if (is_str_redirect(cmd[i]))
		{
			if (is_str_redirect(cmd[i + 1]))
				return (redirection_error());
			if (redirection_regexp(cmd[i]))
				return (1);
		}
		get_info(cmd[i], &info);
		if (!info->filename)
			return (redirection_error());
		else
		{
			if (is_dir(info->filename))
			{
				ft_putstr_fd("shell: is a directory ", 2);
				ft_putstr_fd(info->filename, 2);
				ft_putstr_fd("\n", 2);
				return (1);
			}
			else if (access(info->filename, W_OK) == -1 && is_real_file(get_value_by_name("PWD"), info->filename))
			{
				ft_putstr_fd("shell: permission denied: ", 2);
				ft_putstr_fd(info->filename, 2);
				ft_putstr_fd("\n", 2);
				return (1);
			}
		}
		i++;
	}
	return (0);
}

void redirect_open(t_redirect *info)
{
	info->file_fd = open(info->filename, info->flags, 0666);
	info->stdoutCopy = dup(info->redirect_fd);
	dup2(info->file_fd, info->redirect_fd);
}

int redirection_error(void)
{
	ft_putstr_fd("parse error\n", 2);
	return (1);
}

int redirection_regexp(char *str)
{
	int i;

	i = 0;
	while (str[i] != '>' && str[i] != '<')
	{
		if (!ft_isdigit(str[i]) && str[i] != '&')
			return (redirection_error());
		else if ((ft_isdigit(str[i]) && str[i + 1] == '&') || (str[i] == '&' && ft_isdigit(str[i + 1])))
			return (redirection_error());
		i++;
	}
	if ((str[i] == '>' && str[i + 1] == '>') || (str[i] == '<' && str[i + 1] == '<'))
	{	
		i++;
		if ((str[i] == '>' && str[i + 1] == '>') || (str[i] == '<' && str[i + 1] == '<'))
			return(redirection_error());
		return (0);
	}
	else if ((str[i] == '>' && str[i+1] != '>') || (str[i] == '<' && str[i+1] != '<'))
		return (0);
	return (redirection_error());
}

void init_redirect(t_redirect *info)
{
	info->filename = NULL;
	info->flags = 0;
	info->file_fd = -1;
	info->redirect_fd = 1;
	info->redirection_direction = 0;
	info->stdoutCopy = -1;
}

void redirect_close(t_redirect *info)
{
	if (info->stdoutCopy >= 0)
	{
		dup2(info->stdoutCopy, info->redirect_fd);
		close(info->stdoutCopy);
		close(info->file_fd);
	}
}