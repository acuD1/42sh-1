/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_arrow_ak.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 15:12:56 by skuppers          #+#    #+#             */
/*   Updated: 2019/05/21 13:18:13 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interface_functions.h"

int8_t				ak_arrow_right(t_registry *shell)
{
	set_redraw_flags(&shell->interface, RD_NONE | RD_CMOVE);
	set_cursor_pos(&shell->interface, shell->interface.cursor.index + 1);
	return (SUCCESS);
}

int8_t				ak_arrow_left(t_registry *shell)
{
	set_redraw_flags(&shell->interface, RD_NONE | RD_CMOVE);
	set_cursor_pos(&shell->interface, shell->interface.cursor.index - 1);
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
