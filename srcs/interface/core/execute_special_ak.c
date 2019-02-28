/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_special_ak.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 15:14:28 by skuppers          #+#    #+#             */
/*   Updated: 2019/02/28 14:37:18 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edit.h"
#include "ft_printf.h"

int	ft_putc(int c)
{
	write(1, &c, 1);
	return (42);
}

int tc_ak_hightab(t_interface_registry *itf_reg)
{
	//Autocompletion
	return (itf_reg->window->cursor_index);
}

int tc_ak_delete(t_interface_registry *itf_reg)
{
	shift_content_left_once(itf_reg->vector,
			itf_reg->window->cursor_index);
	itf_reg->window->cursor_index = redraw_input_line(itf_reg);
	return (itf_reg->window->cursor_index);
}

int tc_ak_backspace(t_interface_registry *itf_reg)
{
	if (itf_reg->window->cursor_index >= 1)
	{
		itf_reg->window->cursor_index = tc_ak_arrow_left(itf_reg);
		shift_content_left_once(itf_reg->vector, itf_reg->window->cursor_index);
		itf_reg->window->cursor_index = redraw_input_line(itf_reg);
	}
	return (itf_reg->window->cursor_index);
}

int tc_ak_home(t_interface_registry *itf_reg)
{
	while (itf_reg->window->cursor_index > 0)
		itf_reg->window->cursor_index = tc_ak_arrow_left(itf_reg);
	return (itf_reg->window->cursor_index);
}

int tc_ak_end(t_interface_registry *itf_reg)
{
	while (itf_reg->window->cursor_index < (int)ft_vctlen(itf_reg->vector))
		itf_reg->window->cursor_index = tc_ak_arrow_right(itf_reg);
	return (itf_reg->window->cursor_index);
}

/**
 *	OVERRIDING PROMPT CONDITION
 */
int tc_ak_enter(t_interface_registry *itf_reg)
{
	return (itf_reg->window->cursor_index);
}

