#include "shell.h"

static int		is_permission_and_exist(char **argv)
{
	struct stat buf;

	substitute_tild(&argv[1]);
	if (argv[1] && argv[2])
	{
		ft_putstr_fd("cd: too many arguments\n", 2);
		return (0);
	}
	else if (lstat(argv[1], &buf) == -1)
	{
		ft_putstr_fd("cd: no such file or directory: ", 2);
		ft_putstr_fd(argv[1] ,2);
		write(2, "\n", 1);
		return (0);
	}
	else if (!(buf.st_mode & S_IXUSR))
	{
		ft_putstr_fd("cd: permission denied: ", 2);
		ft_putstr_fd(argv[1] ,2);
		write(2, "\n", 1);
		return (0);
	}
	else if (S_ISREG(buf.st_mode))
	{
		ft_putstr_fd("cd: not a directory: ", 2);
		ft_putstr_fd(argv[1] ,2);
		write(2, "\n", 1);
		return (0);
	}	
	return (1);
}

int bi_cd(char **argv)
{
	char		buf[MAXPATHLEN];

	if (!argv[1])
	{
		getcwd(buf, MAXPATHLEN);
		change_list("OLWDPWD", buf);
		chdir(get_value_by_name("HOME"));
		getcwd(buf, MAXPATHLEN);
		change_list("PWD", buf);
	}
	else if (ft_strequ(argv[1], "-"))
	{
		chdir(get_value_by_name("OLDPWD"));
		getcwd(buf, MAXPATHLEN);
		change_list("OLDPWD", get_value_by_name("PWD"));
		change_list("PWD", buf);
	}
	else if (is_permission_and_exist(argv))
	{
		chdir(argv[1]);
		change_list("OLWDPWD", get_value_by_name("PWD"));
		getcwd(buf, MAXPATHLEN);
		change_list("PWD", buf);
	}
	return (1);
}