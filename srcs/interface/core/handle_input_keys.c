/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input_keys.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 14:40:53 by skuppers          #+#    #+#             */
/*   Updated: 2019/03/05 13:21:33 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"
#include "line_edit.h"
#include "log.h"

static short 	is_printable(char c[READ_SIZE])
{
	if (c[1] == 0 && ft_isprint(c[0]))
		return (1);
	return (0);
}

static short is_same_keycode(char c[READ_SIZE], int kc[])
{
	int i;

	i = 0;
	while (i < 8)
	{
		if (c[i] != kc[i])
			return (0);
		i++;
	}
	return (1);
}

static unsigned int handle_printable_char(char c[READ_SIZE], t_interface_registry *itf_reg)
{
	unsigned int 	tmp_index;
	t_vector		*vector_ptr;

	vector_ptr = itf_reg->vector;
	tmp_index = itf_reg->window->cursor_index;
	if (tmp_index > (vector_ptr->size - 2))
		ft_vctrescale(itf_reg->vector);
	vector_ptr = itf_reg->vector;
	if (ft_vctlen(vector_ptr) != tmp_index)
	{
		tputs(itf_reg->termcaps->begin_insertion, 1, &ft_putc);
		print_words(c, itf_reg);
		tputs(itf_reg->termcaps->end_insertion, 1, &ft_putc);
		shift_content_right_once(vector_ptr, tmp_index);
		vector_ptr->buffer[tmp_index] = c[0];
		redraw_after_cursor(itf_reg);
	}
	else
	{
		vector_ptr->buffer[tmp_index] = c[0];
		print_words(c, itf_reg);
	}
	return (itf_reg->window->cursor_index);
}

//ft_printf_fd(1, "|%d|%d|%d|%d|%d|%d|%d|%d|\n", c[0], c[1], c[2], c[3], c[4], c[5], c[6], c[7]);

int		handle_input_key(char c[READ_SIZE], t_interface_registry *itf_reg)
{
	unsigned int 	i;

	if (is_printable(c))
		return (handle_printable_char(c, itf_reg));
	else
	{
		i = 0;
		while (i < AK_AMOUNT)
		{
			if (is_same_keycode(c, itf_reg->ak_keycodes[i]))
				return ((itf_reg->tc_call)[i](itf_reg));
			++i;
		}
	}
	return (itf_reg->window->cursor_index);
}
