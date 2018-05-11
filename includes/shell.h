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

typedef struct s_env
{
	char *name;
	char *value;
	struct s_env *next;
}               t_env;

typedef struct s_shell
{
	t_env *environ;
}               t_shell;

t_shell g_data;

t_env		*copy_env(char **env);
void        print_env(void);
void        shell_init(char **env);
void        shell_loop(void);
void        shell_exit(void);
void		signals(void);
void        print_prompt(void);

#endif
