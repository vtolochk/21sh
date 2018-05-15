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

//void print_prompt(void)
//{
//	ft_putstr_fd(BLUE, 1);
//	ft_putstr_fd("prompt ;) $> ", 1);
//	ft_putstr_fd(EOC, 1);
//}
void		print_prompt(void)
{
	char *pwd;
	char *name;
	char host[255];

	gethostname(host, 255);
	pwd = "home";
	name = "vtolochk";
	ft_printf("%magenta%[%s]%yellow%[%s]%eoc%%green%[%s]%eoc% $>", name, host, pwd);
}
