/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_word_jumping_ak.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 11:33:40 by skuppers          #+#    #+#             */
/*   Updated: 2019/04/11 17:06:35 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edit.h"
#include "ft_printf.h"

int		tc_ak_next_word(t_interface *itf)
{
	uint32_t	next_char;

	if (validate_interface_content(itf) != 0)
		return (-1);

	if (itf->cursor->index == ft_vctlen(itf->line))
		return (-1);
	else
	{
		next_char = 0;
		next_char = get_next_char(itf->line->buffer, itf->cursor->index, 1);
		while (itf->cursor->index != next_char)
			tc_ak_arrow_right(itf);
	}
	return (0);
}

int		tc_ak_prev_word(t_interface *itf)
{
	uint32_t	prev_char;

	if (validate_interface_content(itf) != 0)
		return (-1);
	if (itf->cursor->index == 0)
		return (-1);
	else
	{
		prev_char = 0;
		prev_char = get_next_char(itf->line->buffer, itf->cursor->index, -1);
		while (itf->cursor->index != prev_char)
			tc_ak_arrow_left(itf);
	}
	return (0);
}

int		tc_ak_ctrl_down(t_interface *itf)
{
	uint32_t	prompt_length;
	uint32_t	 moves;
	uint32_t	line_length;
	uint32_t	lines_amount;

	if (validate_interface_content(itf) != 0)
		return (-1);
	moves = 0;

	prompt_length = get_prompt_len(itf);

	line_length = (ft_vctlen(itf->line) - 1);

	lines_amount = ((line_length + prompt_length)
			/ itf->window->cols) + 1;

	if (lines_amount > 1)
	{
		while (moves < itf->window->cols)
		{
			tc_ak_arrow_right(itf);
			++moves;
		}
	}
	return (0);
}

int		tc_ak_ctrl_up(t_interface *itf)
{
	uint32_t	moves;
	uint32_t	prompt_length;
	uint32_t	line_length;
	uint32_t	lines_amount;
	uint32_t	cursor_line;

	if (validate_interface_content(itf) != 0)
		return (-1);
	moves = 0;

	prompt_length = get_prompt_len(itf);

	line_length = (ft_vctlen(itf->line) - 1);

	lines_amount = ((line_length + prompt_length)
			/ itf->window->cols) + 1;

	cursor_line = itf->cursor->y;
	if (cursor_line == 1 && itf->cursor->x <= prompt_length)
		tc_ak_home(itf);

	if (lines_amount > 1 && cursor_line > 0)
	{
		while (moves < itf->window->cols)
		{
			tc_ak_arrow_left(itf);
			++moves;
		}
	}
	return (0);
}
