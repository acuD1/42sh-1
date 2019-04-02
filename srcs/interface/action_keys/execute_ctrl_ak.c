/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_ctrl_ak.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/09 07:30:12 by skuppers          #+#    #+#             */
/*   Updated: 2019/04/02 10:33:29 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edit.h"
#include "ft_printf.h"

int		tc_ak_ctrl_d(t_interface_registry *itf_reg)
{
	if (itf_reg->vector->buffer[0] == '\0')
		itf_reg->vector->buffer[0] = 4;
	else
	{
		itf_reg->window->cursor_index = tc_ak_delete(itf_reg);
	}
	return (itf_reg->window->cursor_index);
}

int		tc_ak_clear_screen(t_interface_registry *itf_reg)
{
	int initial_cursor_pos;

	initial_cursor_pos = itf_reg->window->cursor_index;
	itf_reg->window->cursor_index = tc_ak_end(itf_reg);
	tputs(itf_reg->termcaps->clear, itf_reg->window->rows, ft_putc);
	redraw_prompt(MAGIC_NUMBER);
	itf_reg->window->cursor_index = redraw_input_line(itf_reg);
	while (itf_reg->window->cursor_index < initial_cursor_pos)
			itf_reg->window->cursor_index = tc_ak_arrow_right(itf_reg);
	return (itf_reg->window->cursor_index);
}
