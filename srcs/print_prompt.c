/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_prompt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtolochk <vtolochk@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/11 12:41:00 by vtolochk          #+#    #+#             */
/*   Updated: 2018/05/11 12:41:00 by vtolochk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void refresh_prompt_len(void)
{
	int new_len;

	new_len = ft_strlen(get_value_by_name("PWD"));
	g_data.prompt_len = new_len + 4;
}

void print_prompt(void)
{
	ft_putstr_fd(BLUE, 2);
	ft_putstr_fd(get_value_by_name("PWD"), 2);
	ft_putstr_fd(EOC, 2);
	ft_putstr_fd(GREY, 2);
	ft_putstr_fd(" $> ", 2);
	ft_putstr_fd(EOC, 2);
	refresh_prompt_len();
}
