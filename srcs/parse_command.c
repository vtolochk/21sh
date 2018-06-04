/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtolochk <vtolochk@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/30 11:32:00 by vtolochk          #+#    #+#             */
/*   Updated: 2018/05/30 11:32:00 by vtolochk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void quoting(void)
{
	char quote;

	while (1)
	{
		quote = check_unclosing();
		if (quote)
			wait_quote(quote);
		else
			break ;
	}
}

void parse_command(void)
{
	quoting();
}