/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_arrow_ak.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 15:12:56 by skuppers          #+#    #+#             */
/*   Updated: 2019/02/07 18:41:27 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edit.h"
#include "ft_printf.h"
#include "log.h"
#include "history.h"

//t_history *g_history_head;
//t_history *g_history_selection;

t_termcaps *g_termcaps;

int tc_ak_arrow_right(t_buffer *vector, t_winsize *ws)
{
	int tmp_idx;

	tmp_idx = ws->cursor_index;

	if (tmp_idx < (int)vector_last_char(vector))
	{
		if (ws->x >= ws->cols - 1)
		{
			tputs(g_termcaps->cs_down, 1, &ft_putc);
			tmp_idx = (tmp_idx + ws->cols);
			ws->y++;

			while (ws->x > 0)
			{
				--tmp_idx;
				ws->x--;
			}
		}
		else
		{
			tputs(g_termcaps->cs_right, 1 , &ft_putc);
			++tmp_idx;
			ws->x++;
		}
	}
	return (tmp_idx);
}

int tc_ak_arrow_left(t_buffer *vector, t_winsize *ws)
{
	(void)vector;
	int		tmp_idx;

	tmp_idx = ws->cursor_index;

	if (tmp_idx >= 1)
	{

		if (ws->x == 0 && ws->y >= 1)
		{
			tputs(g_termcaps->cs_up, 1, &ft_putc);
			ws->y--;

			while (ws->x < ws->cols)
			{
				tputs(g_termcaps->cs_right, 1, &ft_putc);
				ws->x++;
			}
			--tmp_idx;
			ws->x--;
		}
		else
		{
			tputs(g_termcaps->cs_left, 1, &ft_putc);
			--tmp_idx;
			ws->x--;
		}
	}
	return (tmp_idx);
}

int tc_ak_arrow_up(t_buffer *vector, t_winsize *ws)
{
	(void)vector;
	return (ws->cursor_index);
}

int tc_ak_arrow_down(t_buffer *vector, t_winsize *ws)
{
	(void)vector;
	return (ws->cursor_index);
}

