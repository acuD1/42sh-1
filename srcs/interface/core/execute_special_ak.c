/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_special_ak.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 15:14:28 by skuppers          #+#    #+#             */
/*   Updated: 2019/02/08 11:42:04 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edit.h"
#include "ft_printf.h"

t_termcaps	*g_termcaps;

int	ft_putc(int c)
{
	write(1, &c, 1);
	return (42);
}

int tc_ak_delete(t_vector *vector, t_winsize *ws)
{
	shift_content_left_once(vector, ws->cursor_index);
	ws->cursor_index = redraw_input_line(vector, ws);
	return (ws->cursor_index);
}

int tc_ak_backspace(t_vector *vector, t_winsize *ws)
{
	if (ws->cursor_index >= 1)
	{
		ws->cursor_index = tc_ak_arrow_left(vector, ws);
		shift_content_left_once(vector, ws->cursor_index);
		ws->cursor_index = redraw_input_line(vector, ws);
	}
	return (ws->cursor_index);
}

int tc_ak_home(t_vector *vector, t_winsize *ws)
{
	while (ws->cursor_index > 0)
		ws->cursor_index = tc_ak_arrow_left(vector, ws);
	return (ws->cursor_index);
}

int tc_ak_end(t_vector *vector, t_winsize *ws)
{
	while (ws->cursor_index < (int)ft_vctlen(vector))
		ws->cursor_index = tc_ak_arrow_right(vector, ws);
	return (ws->cursor_index);
}

/**
 *	OVERRIDING PROMPT CONDITION
 */
int tc_ak_enter(t_vector *vector, t_winsize *ws)
{
	(void)vector;
	return (ws->cursor_index);
}

