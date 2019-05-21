/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_special_ak.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 15:14:28 by skuppers          #+#    #+#             */
/*   Updated: 2019/05/21 16:13:28 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interface_functions.h"

int8_t		tc_ak_hightab(t_registry *shell)
{
	(void)shell;
	return (SUCCESS);
}

int8_t		ak_delete(t_registry *shell)
{
	vct_del_char(shell->interface.line, shell->interface.cursor.index);
	set_redraw_flags(&shell->interface, RD_FPTE | RD_CMOVE);
	set_redraw_bounds(&shell->interface,
					shell->interface.cursor.index - 1, 0);
	set_cursor_pos(&shell->interface, shell->interface.cursor.index);
	return (SUCCESS);
}

int8_t		ak_backspace(t_registry *shell)
{
	if (shell->interface.cursor.index == 0)
		return (SUCCESS);
	vct_del_char(shell->interface.line, shell->interface.cursor.index - 1);

	set_redraw_flags(&shell->interface, RD_LINE | RD_CMOVE);
//	set_redraw_bounds(&shell->interface, shell->interface.cursor.index - 1,
//					vct_len(shell->interface.window.displayed_line) + 1);
	set_cursor_pos(&shell->interface, shell->interface.cursor.index - 1);
	return (SUCCESS);
}
