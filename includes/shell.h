/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtolochk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/08 16:34:15 by vtolochk          #+#    #+#             */
/*   Updated: 2018/05/08 16:45:18 by vtolochk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

//global list variable for environment variables


#include "../Libft/includes/libft.h"
#include <termios.h>
#include <term.h>
#include <termcap.h>
#include <sys/ioctl.h>

# define EOC "\e[0m"
# define RED "\e[38;5;197m"
# define BLUE "\e[38;5;69m"

# define TAB '\t'
# define ESC 27
# define ENTER 10
# define BACKSPACE 127
# define ARROW_UP "[A"
# define ARROW_DOWN "[B"
# define ARROW_LEFT "[D"
# define ARROW_RIGHT "[C"

# define FAIL 1
# define OK 0

typedef struct s_env
{
	char *name;
	char *value;
	struct s_env *next;
}               t_env;

typedef struct s_shell
{
	char key[8];
	int cursor_x;
	t_env *environ;
	int command_len;
	char command[4096];
	struct termios tty;
	struct termios old_tty;
	struct winsize win_size;
}               t_shell;

t_shell g_data;

t_env		*copy_env(char **env);
void        print_env(void);
void        annulment(void);
void        shell_init(char **env);
void        shell_loop(void);
void        shell_exit(void);
void		signals(void);
void        print_prompt(void);
void        set_old_mode(void);
int         set_shell_mode(void);
void	    get_screen_size(void);
void        cursor_actions(void);
void        delete_char(void);
void        insert_char(void);
int			print_command(int sign);
void        print_capability(char *name);

#endif
