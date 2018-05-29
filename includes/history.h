/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtolochk <vtolochk@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 14:11:00 by vtolochk          #+#    #+#             */
/*   Updated: 2018/05/29 14:11:00 by vtolochk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HISTORY_H
# define HISTORY_H

# define EXIT 1
# define WORK 0

t_history *history_new_node(char *command);
void save_last_command(char **last_command);
void history_go_to_the_first_element(void);
void history_save(void);
void history_up(void);
void history_free(void);
void history_actions(int command);
void history_down(char *last_command);
void clean_screen_after_prompt(void);

#endif
