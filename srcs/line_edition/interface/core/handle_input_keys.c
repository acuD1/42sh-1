/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input_keys.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 14:40:53 by skuppers          #+#    #+#             */
/*   Updated: 2019/04/09 19:10:20 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edit.h"
#include "log.h"

static short		is_printable(char c[READ_SIZE])
{
	if (c[1] == 0 && ft_isprint(c[0]))
		return (1);
	return (0);
}

void	handle_printable_char(char c,
		t_interface_registry *itf_reg)
{
	unsigned int	tmp_index;
	t_vector		*vector_ptr;

	vector_ptr = itf_reg->line;
	tmp_index = itf_reg->window->cursor;
	if (ft_vctlen(itf_reg->line) >= (size_t)itf_reg->window->max_line_len)
		return ;
	if (tmp_index > (vector_ptr->size - 2))
		ft_vctrescale(itf_reg->line);
	vector_ptr = itf_reg->line;
	if (tmp_index != ft_vctlen(vector_ptr))
	{
		shift_content_right_once(vector_ptr, tmp_index);
		vector_ptr->buffer[tmp_index] = c;
	}
	else
		vector_ptr->buffer[ft_vctlen(vector_ptr)] = c;
	redraw_after_cursor(itf_reg);
	tc_ak_arrow_right(itf_reg);
}

unsigned long		compute_mask(char c[READ_SIZE])
{
	unsigned short 	shift;
	unsigned short 	index;
	unsigned long 	value;
	unsigned long 	tmp;

	shift = 56;
	index = 0;
	value = 0;
	tmp = 0;
	while (index < 8 && c[index] != 0)
	{
		tmp = c[index++];
		tmp <<= shift;
		value |= tmp;
		shift -= 8;
	}
	return (value);
}

//	ft_dprintf(1, "|%d|%d|%d|%d|%d|%d|%d|%d|\n",c[0], c[1], c[2], c[3], c[4], c[5], c[6], c[7]);

void				handle_input_key(char c[READ_SIZE],
				t_interface_registry *itf_reg)
{
	int 			index;
	unsigned long	value;

	if (is_printable(c))
		handle_printable_char(c[0], itf_reg);
	else
	{
		index = 0;
		value = compute_mask(c);
		while (index < AK_AMOUNT)
		{
			if (value == itf_reg->ak_masks[index])
					(itf_reg->tc_call)[index](itf_reg);
			++index;
		}
	}
}
