/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_word_jumping_ak.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 11:33:40 by skuppers          #+#    #+#             */
/*   Updated: 2019/04/02 13:27:52 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edit.h"
#include "ft_printf.h"

int		tc_ak_next_word(t_interface_registry *itf_reg)
{
	int	next_char;

	if (itf_reg->window->cursor_index == (int)ft_vctlen(itf_reg->vector))
		return (itf_reg->window->cursor_index);
	else
	{
		next_char = 0;
		next_char = get_next_char(itf_reg->vector->buffer, itf_reg->window->cursor_index, 1);
		while (itf_reg->window->cursor_index != next_char)
			itf_reg->window->cursor_index = tc_ak_arrow_right(itf_reg);
	}
	return (itf_reg->window->cursor_index);
}

int		tc_ak_prev_word(t_interface_registry *itf_reg)
{
	int prev_char;

	if (itf_reg->window->cursor_index == 0)
		return (0);
	else
	{
		prev_char = 0;
		prev_char = get_next_char(itf_reg->vector->buffer, itf_reg->window->cursor_index, -1);
		while (itf_reg->window->cursor_index != prev_char)
			itf_reg->window->cursor_index = tc_ak_arrow_left(itf_reg);
	}
	return (itf_reg->window->cursor_index);
}

int		tc_ak_ctrl_down(t_interface_registry *itf_reg)
{
	size_t moves;
	size_t line_length;
	size_t lines_amount;

	moves = 0;
	line_length = (ft_vctlen(itf_reg->vector) - 1);
	lines_amount = ((line_length + PROMPT_TEXT_LENGTH)
			/ itf_reg->window->cols) + 1;
	if (lines_amount > 1)
	{
		while (moves < itf_reg->window->cols)
		{
			itf_reg->window->cursor_index = tc_ak_arrow_right(itf_reg);
			++moves;
		}
	}
	return (itf_reg->window->cursor_index);
}

int		tc_ak_ctrl_up(t_interface_registry *itf_reg)
{
	size_t moves;
	size_t line_length;
	size_t lines_amount;
	size_t cursor_line;

	moves = 0;
	line_length = (ft_vctlen(itf_reg->vector) - 1);
	lines_amount = ((line_length + PROMPT_TEXT_LENGTH)
			/ itf_reg->window->cols) + 1;
	cursor_line = itf_reg->window->y;
	if (cursor_line == 1 && itf_reg->window->x <= PROMPT_TEXT_LENGTH)
		return (tc_ak_home(itf_reg));
	if (lines_amount > 1 && cursor_line > 0)
	{
		while (moves < itf_reg->window->cols)
		{
			itf_reg->window->cursor_index = tc_ak_arrow_left(itf_reg);
			++moves;
		}
	}
	return (itf_reg->window->cursor_index);
}
