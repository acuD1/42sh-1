/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_ctrl_ak.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/09 07:30:12 by skuppers          #+#    #+#             */
/*   Updated: 2019/04/09 19:17:21 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edit.h"
#include "ft_printf.h"

int		tc_ak_ctrl_d(t_interface_registry *itf)
{
	if (itf->line->buffer[0] == '\0')
		itf->line->buffer[0] = 4;
	//[1] = '\0';
	else
		tc_ak_delete(itf);
	return (0);
}

int		tc_ak_clear_screen(t_interface_registry *itf)
{
	size_t initial_cursor_pos;

	if (validate_interface_content(itf) != 0)
		return (-1);

	initial_cursor_pos = itf->window->cursor;
	tc_ak_end(itf);
	tputs(itf->termcaps->clear, itf->window->rows, ft_putc);
	//magic nbr
	redraw_prompt(ft_atoi(INT_MAGIC_NUMBER));
	itf->window-> cursor = redraw_input_line(itf);
	while (itf->window->cursor < initial_cursor_pos)
			tc_ak_arrow_right(itf);
	return (0);
}
