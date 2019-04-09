/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_word_jumping_ak.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 11:33:40 by skuppers          #+#    #+#             */
/*   Updated: 2019/04/09 19:08:21 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edit.h"
#include "ft_printf.h"

int		tc_ak_next_word(t_interface_registry *itf)
{
	size_t	next_char;

	if (validate_interface_content(itf) != 0)
		return (-1);

	if (itf->window->cursor == ft_vctlen(itf->line))
		return (-1);
	else
	{
		next_char = 0;
		next_char = get_next_char(itf->line->buffer, itf->window->cursor, 1);
		while (itf->window->cursor != next_char)
			tc_ak_arrow_right(itf);
	}
	return (0);
}

int		tc_ak_prev_word(t_interface_registry *itf)
{
	size_t prev_char;

	if (validate_interface_content(itf) != 0)
		return (-1);
	if (itf->window->cursor == 0)
		return (-1);
	else
	{
		prev_char = 0;
		prev_char = get_next_char(itf->line->buffer, itf->window->cursor, -1);
		while (itf->window->cursor != prev_char)
			tc_ak_arrow_left(itf);
	}
	return (0);
}

int		tc_ak_ctrl_down(t_interface_registry *itf)
{
	size_t prompt_length;
	size_t moves;
	size_t line_length;
	size_t lines_amount;

	if (validate_interface_content(itf) != 0)
		return (-1);
	prompt_length = ft_strlen(get_intern_var(itf->sh_reg, itf->interface_state));
	moves = 0;
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

int		tc_ak_ctrl_up(t_interface_registry *itf)
{
	size_t moves;
	size_t prompt_length;
	size_t line_length;
	size_t lines_amount;
	size_t cursor_line;

	if (validate_interface_content(itf) != 0)
		return (-1);
	moves = 0;
	prompt_length = ft_strlen(get_intern_var(itf->sh_reg, itf->interface_state));
	line_length = (ft_vctlen(itf->line) - 1);
	lines_amount = ((line_length + prompt_length)
			/ itf->window->cols) + 1;
	cursor_line = itf->window->y;
	if (cursor_line == 1 && itf->window->x <= prompt_length)
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
