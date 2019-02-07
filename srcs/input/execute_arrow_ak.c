/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_arrow_ak.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 15:12:56 by skuppers          #+#    #+#             */
/*   Updated: 2019/01/31 13:11:41 by skuppers         ###   ########.fr       */
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
//			ft_printf_fd(2, "TERMCAP_RIGHT\n");
			tputs(g_termcaps->cs_right, 1 , &ft_putc);
			++tmp_idx;
			ws->x++;
		}
	}

//	ft_printf_fd(2, "[MOVE_CURSOR_R] - x:%d|y:%d|tmp:%d|vlc:%d\n", ws->x, ws->y, tmp_idx, vector_last_char(vector));

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
//			tmp_idx = (tmp_idx - ws->cols - 1);
			ws->y--;

			while (ws->x < ws->cols)
			{
				tputs(g_termcaps->cs_right, 1, &ft_putc);
//				++tmp_idx;
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
//	ft_printf_fd(2, "[MOVE_CURSOR_L] - x:%d|y:%d|tmp:%d\n", ws->x, ws->y, tmp_idx);
	}
	return (tmp_idx);
}

int tc_ak_arrow_up(t_buffer *vector, t_winsize *ws)
{
	(void)vector;
	//	if (g_history_selection == NULL)
	//		g_history_selection	= g_history_head;
	//	else
	//		g_history_selection = g_history_selection->next;

	//TODO:
	// delete the vector buffer

	// delete whats on screen entirely -> several lines
	// store history selection in vector
	// rewrite (?prompt?) and the history command
	//
	//ft_bzero(vector->buffer, vector->current_size);
	//ft_strcpy(vector->buffer, g_history_selection->command);

	//if vector is empty
	//		get first history_entry (first is last command entered)
	//else
	//		get first history entry that (begins with X)

	return (ws->cursor_index);
}

int tc_ak_arrow_down(t_buffer *vector, t_winsize *ws)
{
	(void)vector;
	//	char *str;
	//
	//	str = tgetstr("le", NULL);
	//	ft_printf_fd(1, "%s", str);

	//	ft_printf_fd(1, "Pressed down ak\n");
	return (ws->cursor_index);
}

