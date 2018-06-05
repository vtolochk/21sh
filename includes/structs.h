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

# define BUFFER_SIZE 4096
# define MAX_COMMANDS 1024


/*
**  Just a random numbers
*/

# define PIPE 42
# define RIGHT_ARR 43
# define LEFT_ARR 44
# define DOUBLE_RIGHT_ARR 45
# define DOUBLE_LEFT_ARR 46


/*
**  if i dont have token
**  the command will save to the cmd_before
**
**
*/

typedef struct s_info
{
	char *cmd_before;
	int  token[24]; // stack ???
	char *cmd_after;
}               t_info;

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
t_info g_cmd_info[MAX_COMMANDS];
//global list variable for environment variables

#endif
