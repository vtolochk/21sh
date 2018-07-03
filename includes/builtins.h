/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtolochk <vtolochk@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 13:31:00 by vtolochk          #+#    #+#             */
/*   Updated: 2018/06/12 13:31:00 by vtolochk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

int check_builtins(char **argv);
int bi_echo(char **argv);
int bi_exit(char **argv);
int bi_clear(char **argv);
int bi_env(char **argv);
int bi_history(char **argv);
int bi_pwd(char **argv);
int bi_setenv(char **argv);
int bi_unsetenv(char **argv);
int bi_cd(char **argv);

#endif
