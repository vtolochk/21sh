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

static char  *second_test(char *arrow_str, char *next_str, int arrows, char c)
{
	int i;
	char quote;
	char *filename;

	i = 0;
	filename = NULL;
	while (arrow_str[i])
	{
		if (arrow_str[i] == '\'' || arrow_str[i] == '\"')
		{
			quote = arrow_str[i];
			i++;
			while (arrow_str[i] && arrow_str[i] != quote)
				i++;
		}
		else if (arrows == (TWO_ARROWS) && arrow_str[i] == c)
		{
			if (count_sign(&arrow_str[i], c) > 2 || (c == '>' && count_sign(&arrow_str[i], '<') > 0) || (c == '<' && count_sign(&arrow_str[i], '>') > 0))
				return (NULL);
			if (arrow_str[i + 2] && arrow_str[i + 2] != c)
				filename = ft_strsub(arrow_str, i + 2, ft_strlen(arrow_str));
			else if (next_str && arrow_str[i + 2] != c)
					filename = ft_strdup(next_str);
			return (filename);
		}
		else if (arrows == (ONE_ARROW) && arrow_str[i] == c)
		{
			if (count_sign(&arrow_str[i], c) > 1 || (c == '>' && count_sign(&arrow_str[i], '<') > 0) || (c == '<' && count_sign(&arrow_str[i], '>') > 0))
				return (NULL);
			if (arrow_str[i + 1])
				filename = ft_strsub(arrow_str, i + 1, ft_strlen(arrow_str));
			else if (next_str)
				filename = ft_strdup(next_str);
			return (filename);
		}
		i++;
	}
	return (filename);
}

void get_info(char **cmd, t_redirect *info)
{
	int i;
	int j;
	char quote;

	i = 0;
	j = 0;
	while (cmd[i])
	{
		if (ft_strchr(cmd[i], '>') || ft_strchr(cmd[i], '<'))
		{
			while (cmd[i][j])
			{
				if (cmd[i][j] == '\'' || cmd[i][j] == '\"')
				{
					quote = cmd[i][j];
					j++;
					while (cmd[i][j] && cmd[i][j] != quote)
						j++;
				}
				else if (cmd[i][j] == '>' && cmd[i][j + 1] == '>')
				{
					info->filename = second_test(cmd[i], cmd[i + 1], TWO_ARROWS, '>');
					info->flags = TWO_ARROWS;
					info->redirection_direction = RIGHT_ARR;
					return ;
				}
				else if (cmd[i][j] == '<' && cmd[i][j + 1] == '<')
				{
					info->filename = second_test(cmd[i], cmd[i + 1], TWO_ARROWS, '<');
					info->flags = TWO_ARROWS;
					info->redirection_direction = LEFT_ARR;
					return ;
				}
				else if (cmd[i][j] == '>')
				{
					info->filename = second_test(cmd[i], cmd[i + 1], ONE_ARROW, '>');
					info->flags = ONE_ARROW;
					info->redirection_direction = RIGHT_ARR;
					return ;
				}
				else if (cmd[i][j] == '<')
				{
					info->filename = second_test(cmd[i], cmd[i + 1], ONE_ARROW, '<');
					info->flags = ONE_ARROW;
					info->redirection_direction = RIGHT_ARR;
					return ;
				}
				j++;
			}
		}
		i++;
	}
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

int validate_redirection(char **cmd)
{
	int i;

	i = 0;
	while (cmd[i])
	{
		if (is_str_redirect(cmd[i]))
		{
			if (!redirection_regexp(cmd[i]))
				return (1);
		}
		i++;
	}
	return (0);
}

void redirect(char **cmd, t_redirect *info)
{
	
	validate_redirection(cmd);
	return;
	get_info(cmd, info);
	if (!info->filename)
		ft_printf("parse error\n");
	else
	{
		if (is_dir(info->filename))
		{
			ft_putstr_fd("shell: is a directory ", 2);
			ft_putstr_fd(info->filename, 2);
			ft_putstr_fd("\n", 2);
		}
		else if (access(info->filename, W_OK) == -1 && is_real_file(get_value_by_name("PWD"), info->filename))
		{
			ft_putstr_fd("shell: permission denied: ", 2);
			ft_putstr_fd(info->filename, 2);
			ft_putstr_fd("\n", 2);
		}
		else
		{
			info->file_fd = open(info->filename, info->flags, 0666);
			info->stdoutCopy = dup(info->redirect_fd);
			dup2(info->file_fd, info->redirect_fd);
		}
	}
}

// int redirection_nb(char **cmd)
// {
// 	int i;
// 	int j;
// 	char quote;
// 	int redirecions;

// 	j = 0;
// 	i = 0;
// 	redirecions = 0;
// 	while (cmd[i])
// 	{
// 		j = 0;
// 		while (cmd[i][j])
// 		{
// 			if (cmd[i][j] == '\'' || cmd[i][j] == '\"')
// 			{
// 				quote = cmd[i][j];
// 				j++;
// 				while (cmd[i][j] && cmd[i][j] != quote)
// 					j++;
// 			}
// 			else if ()
// 		}
// 		i++;
// 	}
// 	return (redirecions);
// }

void init_redirect(t_redirect *info)
{
	info->filename = NULL;
	info->flags = 0;
	info->file_fd = -1;
	info->redirect_fd = 1;
	info->redirection_direction = 0;
	info->stdoutCopy = -1;
}

void close_redirect(t_redirect *info)
{
	if (info->stdoutCopy >= 0)
	{
		dup2(info->stdoutCopy, info->redirect_fd);
		close(info->stdoutCopy);
		close(info->file_fd);
	}
}

