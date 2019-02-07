/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_special_ak.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 15:14:28 by skuppers          #+#    #+#             */
/*   Updated: 2019/02/07 17:40:35 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edit.h"
#include "ft_printf.h"

// TODO: DEFINE PROMPT SIZE

t_termcaps	*g_termcaps;

int	ft_putc(int c)
{
	write(1, &c, 1);
	return (42);
}

int tc_ak_delete(t_buffer *vector, t_winsize *ws)
{
//	ft_printf_fd(2, "----------begin suppr----------\n");
	shift_content_left_once(vector, ws->cursor_index);

	ws->cursor_index = redraw_input_line(vector, ws);
//	ft_printf_fd(2, "---------- end  suppr----------\n");

	ft_printf_fd(2, "[DELETE_CHAR] - x:%d|y:%d|idx:%d\n", ws->x, ws->y, ws->cursor_index);

	return (ws->cursor_index);
}

int tc_ak_backspace(t_buffer *vector, t_winsize *ws)
{
	if (ws->cursor_index >= 1)
	{
		ws->cursor_index = tc_ak_arrow_left(vector, ws);
		shift_content_left_once(vector, ws->cursor_index);
		ws->cursor_index = redraw_input_line(vector, ws);
	}
	return (ws->cursor_index);
}

int tc_ak_home(t_buffer *vector, t_winsize *ws)
{
	while (ws->cursor_index > 0)
		ws->cursor_index = tc_ak_arrow_left(vector, ws);

		ft_printf_fd(2, "[MOVE_CURSOR_HOME] - x:%d|y:%d|idx:%d\n", ws->x, ws->y, ws->cursor_index);

	return (ws->cursor_index);
}

int tc_ak_end(t_buffer *vector, t_winsize *ws)
{
	while (ws->cursor_index < (int)vector_last_char(vector))
		ws->cursor_index = tc_ak_arrow_right(vector, ws);

		ft_printf_fd(2, "[MOVE_CURSOR_END] - x:%d|y:%d|idx:%d\n", ws->x, ws->y, ws->cursor_index);

	return (ws->cursor_index);
}

/**
 *	OVERRIDING PROMPT CONDITION
 */
int tc_ak_enter(t_buffer *vector, t_winsize *ws)
{
	(void)vector;
	//Send input to parser
	//	ft_printf_fd(1, "Pressed enter\n");
	return (ws->cursor_index);
}

