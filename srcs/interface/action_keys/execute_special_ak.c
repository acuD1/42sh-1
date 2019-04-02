/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_special_ak.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 15:14:28 by skuppers          #+#    #+#             */
/*   Updated: 2019/04/02 09:38:15 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edit.h"
#include "ft_printf.h"

/*
**	Autocompletion
*/

int	tc_ak_hightab(t_interface_registry *itf_reg)
{
	return (itf_reg->window->cursor_index);
}

int	tc_ak_delete(t_interface_registry *itf_reg)
{
	shift_content_left_once(itf_reg->vector,
			itf_reg->window->cursor_index);
	itf_reg->window->cursor_index = redraw_after_cursor(itf_reg);
	return (itf_reg->window->cursor_index);
}

int	tc_ak_backspace(t_interface_registry *itf_reg)
{
	if (itf_reg->window->cursor_index >= 1)
	{
		itf_reg->window->cursor_index = tc_ak_arrow_left(itf_reg);
		shift_content_left_once(itf_reg->vector, itf_reg->window->cursor_index);
		itf_reg->window->cursor_index = redraw_after_cursor(itf_reg);
	}
	return (itf_reg->window->cursor_index);
}
