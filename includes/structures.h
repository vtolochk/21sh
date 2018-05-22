/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtolochk <vtolochk@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 17:04:00 by vtolochk          #+#    #+#             */
/*   Updated: 2018/05/22 17:04:00 by vtolochk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

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
	int line;
	int cursor;
	char key[8];
	t_env *environ;
	t_history *list;
	int prompt_len;
	int command_len;
	char buffer[4096];
	char command[4096];
	struct termios tty;
	struct termios old_tty;
	struct winsize win_size;
}               t_shell;

#endif
