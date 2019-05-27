/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_arrow_ak.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 15:12:56 by skuppers          #+#    #+#             */
/*   Updated: 2019/05/27 16:33:55 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interface_functions.h"

int8_t				ak_arrow_right(t_registry *shell)
{
	set_redraw_flags(&shell->interface, RD_NONE | RD_CMOVE);


	int8_t offset;
	offset = 1;
	if (shell->interface.cursor.index >= vct_len(shell->interface.line))
			offset = 0;
	if (shell->interface.visual_mode == TRUE)
		shell->interface.vis_stop = shell->interface.cursor.index + offset;
	set_cursor_pos(&shell->interface, shell->interface.cursor.index + offset);

	return (SUCCESS);
}

int8_t				ak_arrow_left(t_registry *shell)
{
	set_redraw_flags(&shell->interface, RD_NONE | RD_CMOVE);


	int8_t offset;
	offset = 1;
	if (shell->interface.cursor.index == 0)
			offset = 0;

	if (shell->interface.visual_mode == TRUE
		&& shell->interface.cursor.index > 0)
		shell->interface.vis_stop = shell->interface.cursor.index - offset;

	set_cursor_pos(&shell->interface, shell->interface.cursor.index - offset);
	return (SUCCESS);
}

int8_t				ak_arrow_up(__unused t_registry *shell)
{
	return (SUCCESS);
}

int8_t				ak_arrow_down(__unused t_registry *shell)
{
	return (SUCCESS);
}
