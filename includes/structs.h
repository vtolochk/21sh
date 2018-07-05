/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtolochk <vtolochk@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 14:22:00 by vtolochk          #+#    #+#             */
/*   Updated: 2018/05/29 14:22:00 by vtolochk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

#include <termios.h>
#include <term.h>
#include <termcap.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/stat.h>
#include <dirent.h>
# include <sys/param.h>

# define MAX_REDIRECT 128
# define BUFFER_SIZE 4096

# define  ONE_ARROW O_CREAT | O_WRONLY | O_TRUNC
# define  TWO_ARROWS O_CREAT | O_WRONLY | O_APPEND

/*
**  Just a random numbers
*/

# define PIPE 42
# define RIGHT_ARR 43
# define LEFT_ARR 44



typedef struct s_redirect
{
	char *filename;
	int flags;
	int file_fd;
	int redirect_fd;
	int redirection_direction;
	int stdoutCopy;
}				t_redirect;

typedef struct s_env
{
	char *name;
	char *value;
	struct s_env *next;
}               t_env;

typedef struct s_history
{
	char *command;
	struct s_history *next;
	struct s_history *prev;
}               t_history;

typedef struct s_shell
{
	int ws_col;
	int line;
	int cursor;
	int rows;
	char key[8];
	t_env *environ;
	t_history *history_list;
	int prompt_len;
	int command_len;
	char buffer[BUFFER_SIZE];
	char command[BUFFER_SIZE];
	struct termios tty;
	struct termios old_tty;
}               t_shell;

t_shell g_data;
t_redirect g_redirect_info[MAX_REDIRECT];
int g_redIter;

#endif
