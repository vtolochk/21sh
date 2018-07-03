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

#include "../Libft/includes/libft.h"
#include "structs.h"
#include "moves.h"
#include "history.h"
#include "copy_cut_paste.h"
#include "builtins.h"

# define EOC "\e[0m"
# define RED "\e[38;5;197m"
# define BLUE "\e[38;5;69m"

# define TAB '\t'
# define ESC 27
# define END    "[F"
# define HOME   "[H"
# define ENTER 10
# define BACKSPACE 127
# define ARROW_UP "[A"
# define ARROW_DOWN "[B"
# define ARROW_LEFT "[D"
# define ARROW_RIGHT "[C"
# define CTRL_UP    "[1;5A"
# define CTRL_DOWN  "[1;5B"
# define CTRL_RIGHT "[1;5C"
# define CTRL_LEFT  "[1;5D"

# define FAIL 1
# define OK 0

# include <stdio.h>

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
void        get_rows(void);
void	    get_screen_size(void);
void        cursor_actions(void);
void        delete_char(void);
void        insert_char(char c);
int			print_command(int sign);
void        capability(char *name);
void        capability_n(char *name, int n);
void        clear_line(void);
char		check_unclosing(void);
void		wait_quote(char quote);
void		quoting(void);
char		**semi_colon_split(char *str);
void		command_process(void);
void		execute_command(char *cmd);
char		**list_to_array(void);
int			list_len(t_env *lst);
char		***form_commands(char **splited);
char 		**smart_whitespaces_split(char *str);
char		**smart_pipe_split(char *str);
void 		free_env_list(t_env *environ);
char		*get_value_by_name(char *name);


void var_dump(char **arr);
void var_dump_arr(char ***arr);

#endif
