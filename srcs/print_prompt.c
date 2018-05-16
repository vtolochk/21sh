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

void print_prompt(void)
{
	ft_putstr_fd(BLUE, 1);
	ft_putstr_fd("$> ", 1);
	ft_putstr_fd(EOC, 1);
//TODO: strlen prompt_str
}
