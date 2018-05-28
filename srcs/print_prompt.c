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
	//temporary
	write(1, "\n", 1);
	//

	ft_putstr_fd(RED, 1);
	ft_putstr_fd("shell > ", 1); // change to the second flow
	ft_putstr_fd(EOC, 1);
	g_data.prompt_len = 8;
//TODO: strlen prompt_str
}
