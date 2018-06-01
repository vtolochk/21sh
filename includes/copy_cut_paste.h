/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_cut_paste.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtolochk <vtolochk@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 15:47:00 by vtolochk          #+#    #+#             */
/*   Updated: 2018/05/29 15:47:00 by vtolochk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COPY_CUT_PASTE_H
# define COPY_CUT_PASTE_H

/*
** ---------------------------
** 		CUT
** ALT-A -> CUT BEFORE CURSOR
** ALT-S -> CUT AFTER CURSOR
** ALT-D -> CUT ALL
** ---------------------------
**			COPY
** ALT-Z -> COPY BEFORE CURSOR
** ALT-X -> COPY AFTER CURSOR
** ALT-C -> COPY ALL
** ---------------------------
**			PASTE
** ALT-V -> PASTE BUFFER
** ---------------------------
*/

# define ALT_A (g_data.key[0] == -61 && g_data.key[1] == -91)
# define ALT_V (g_data.key[0] == -30 && g_data.key[1] == -120 && g_data.key[2] == -102)
# define ALT_Z (g_data.key[0] == -50 && g_data.key[1] == -87)
# define ALT_X (g_data.key[0] == -30 && g_data.key[1] == -119 && g_data.key[2] == -120)
# define ALT_C (g_data.key[0] == -61 && g_data.key[1] == -89)
# define ALT_S (g_data.key[0] == -61 && g_data.key[1] == -97)
# define ALT_D (g_data.key[0] == -30 && g_data.key[1] == -120 && g_data.key[2] == -126)

void cut(void);
void copy(void);
void paste(void);
void copy_paste_actions(void);

#endif
