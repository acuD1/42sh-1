/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_keys.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 11:19:21 by skuppers          #+#    #+#             */
/*   Updated: 2019/02/07 18:40:38 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "log.h"
#include "line_edit.h"
#include "ft_printf.h"

int	(*tc_call[AK_AMOUNT])(t_buffer *vector, t_winsize *ws);
int	ak_keycodes[AK_AMOUNT][READ_SIZE];
t_termcaps	*g_termcaps;

static short 	is_printable(char c[READ_SIZE])
{
	if (c[1] == 0 && c[0] >= 32 && c[0] <= 126)
		return (1);
	return (0);
}

static short is_same_keycode(char c[READ_SIZE], int kc[])
{
	if (c[0] == kc[0] && c[1] == kc[1] && c[2] == kc[2] && c[3] == kc[3]
			&& c[4] == kc[4] && c[5] == kc[5] && c[6] == kc[6] && c[7] == kc[7])
		return (1);
	return (0);
}

unsigned int handle_printable_char(char c[READ_SIZE],
		t_buffer *vector, t_winsize *ws)
{
	unsigned int tmp_idx;

	tmp_idx = ws->cursor_index;
	if (tmp_idx > (vector->current_size - 2))
		vector_rescale(vector);
	if (vector_last_char(vector) != tmp_idx)
	{
		tputs(g_termcaps->begin_insertion, 1, &ft_putc);
		print_words(c, ws);
		tputs(g_termcaps->end_insertion, 1, &ft_putc);
		shift_content_right_once(vector, tmp_idx);
		vector->buffer[tmp_idx] = c[0];
		redraw_input_line(vector, ws);
	}
	else
	{
		vector->buffer[tmp_idx] = c[0];
		print_words(c, ws);
	}
	return (ws->cursor_index);
}

int		handle_input_key(char c[READ_SIZE],
		t_buffer *v_buffer, t_winsize *ws)
{
	unsigned int 	i;

	if (is_printable(c))
		return (handle_printable_char(c, v_buffer, ws));
	else
	{
	//		ft_prints_fd(1, "|%d|%d|%d|%d|%d|%d|%d|%d|\n", c[0], c[1], c[2], c[3], c[4], c[5], c[6], c[7]);
		i = 0;
		while (i < AK_AMOUNT)
		{
			if (is_same_keycode(c, ak_keycodes[i]))
				return (*tc_call[i])(v_buffer, ws);
			++i;
		}
	}
	return (ws->cursor_index);
}
