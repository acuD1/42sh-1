/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_ctrl_ak.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/09 07:30:12 by skuppers          #+#    #+#             */
/*   Updated: 2019/03/02 12:08:46 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edit.h"
#include "ft_printf.h"

int		tc_ak_ctrl_d(t_interface_registry *itf_reg)
{
	if (itf_reg->vector->buffer[0] == '\0')
		itf_reg->vector->buffer[0] = 4;
	else
	{
		itf_reg->window->cursor_index = tc_ak_delete(itf_reg);
	}
	return (itf_reg->window->cursor_index);
}

int		tc_ak_next_word(t_interface_registry *itf_reg)
{
	if (itf_reg->window->cursor_index == (int)ft_vctlen(itf_reg->vector))
		return (itf_reg->window->cursor_index);
	else
	{
		while (itf_reg->window->cursor_index < (int)ft_vctlen(itf_reg->vector)
				&& itf_reg->vector->buffer[itf_reg->window->cursor_index] != ' ')
			itf_reg->window->cursor_index = tc_ak_arrow_right(itf_reg);
		while (itf_reg->window->cursor_index < (int)ft_vctlen(itf_reg->vector)
				&& (itf_reg->vector->buffer[itf_reg->window->cursor_index] == ' '))
			itf_reg->window->cursor_index = tc_ak_arrow_right(itf_reg);
	}
	return (itf_reg->window->cursor_index);
}

int		tc_ak_prev_word(t_interface_registry *itf_reg)
{
	if (itf_reg->window->cursor_index == 0)
		return (0);
	else
	{
		while (itf_reg->window->cursor_index > 0
				&& itf_reg->vector->buffer[itf_reg->window->cursor_index] != ' ')
			itf_reg->window->cursor_index = tc_ak_arrow_left(itf_reg);
		while (itf_reg->window->cursor_index > 0
				&& (itf_reg->vector->buffer[itf_reg->window->cursor_index] == ' '))
			itf_reg->window->cursor_index = tc_ak_arrow_left(itf_reg);
	}
	return (itf_reg->window->cursor_index);
}

static int cut_vector(t_vector *vect, t_winsize *ws, int before)
{
	char	*tmp;
	char	*foobar;

	tmp = ft_strnew(vect->size);
	if (before > 0)
	{
		foobar = ft_strsub(vect->buffer, ws->cursor_index, ft_vctlen(vect));
		tmp = ft_strcpy(tmp, foobar);
		ft_strdel(&foobar);
	}
	else
		tmp = ft_strncpy(tmp, vect->buffer, ws->cursor_index);
	ft_strdel(&(vect->buffer));
	vect->buffer = tmp;
	return (0);
}

int		tc_ak_cut_before_cursor(t_interface_registry *itf_reg)
{
	ft_bzero(itf_reg->clipboard->buffer, itf_reg->clipboard->size);
	while (itf_reg->clipboard->size < itf_reg->vector->size)
		ft_vctrescale(itf_reg->clipboard);
	itf_reg->clipboard->buffer = ft_strncpy(itf_reg->clipboard->buffer, itf_reg->vector->buffer, itf_reg->window->cursor_index);
	cut_vector(itf_reg->vector, itf_reg->window, 1);
	redraw_input_line(itf_reg);
	return (itf_reg->window->cursor_index);
}

int		tc_ak_cut_after_cursor(t_interface_registry *itf_reg)
{
	char *tmp;

	ft_bzero(itf_reg->clipboard->buffer, itf_reg->clipboard->size);
	while (itf_reg->clipboard->size < itf_reg->vector->size)
		ft_vctrescale(itf_reg->clipboard);
	tmp = ft_strsub(itf_reg->vector->buffer, itf_reg->window->cursor_index, ft_vctlen(itf_reg->vector));
	itf_reg->clipboard->buffer = ft_strcpy(itf_reg->clipboard->buffer, tmp);
	ft_strdel(&tmp);
	cut_vector(itf_reg->vector, itf_reg->window, -1);
	redraw_input_line(itf_reg);
	return (itf_reg->window->cursor_index);
}

int		tc_ak_cut_line(t_interface_registry *itf_reg)
{
	ft_bzero(itf_reg->clipboard->buffer, itf_reg->clipboard->size);
	while (itf_reg->clipboard->size < itf_reg->vector->size)
		ft_vctrescale(itf_reg->clipboard);
	itf_reg->clipboard->buffer = ft_strcpy(itf_reg->clipboard->buffer, itf_reg->vector->buffer);
	ft_bzero(itf_reg->vector->buffer, itf_reg->vector->size);
	redraw_input_line(itf_reg);
	return (itf_reg->window->cursor_index);
}

int		tc_ak_copy_before_cursor(t_interface_registry *itf_reg)
{
	ft_bzero(itf_reg->clipboard->buffer, itf_reg->clipboard->size);
	while (itf_reg->clipboard->size < itf_reg->vector->size)
		ft_vctrescale(itf_reg->clipboard);
	itf_reg->clipboard->buffer = ft_strncpy(itf_reg->clipboard->buffer, itf_reg->vector->buffer, itf_reg->window->cursor_index);
	return (itf_reg->window->cursor_index);
}

int		tc_ak_copy_after_cursor(t_interface_registry *itf_reg)
{
	char	*tmp;

	ft_bzero(itf_reg->clipboard->buffer, itf_reg->clipboard->size);
	while (itf_reg->clipboard->size < itf_reg->vector->size)
		ft_vctrescale(itf_reg->clipboard);
	tmp = ft_strsub(itf_reg->vector->buffer, itf_reg->window->cursor_index, ft_vctlen(itf_reg->vector));
	itf_reg->clipboard->buffer = ft_strcpy(itf_reg->clipboard->buffer, tmp);
	ft_strdel(&tmp);
	return (itf_reg->window->cursor_index);
}

int		tc_ak_copy_line(t_interface_registry *itf_reg)
{
	ft_bzero(itf_reg->clipboard->buffer, itf_reg->clipboard->size);
	while (itf_reg->clipboard->size < itf_reg->vector->size)
		ft_vctrescale(itf_reg->clipboard);
	itf_reg->clipboard->buffer = ft_strcpy(itf_reg->clipboard->buffer, itf_reg->vector->buffer);
	return (itf_reg->window->cursor_index);
}

int		tc_ak_paste_clipboard(t_interface_registry *itf_reg)
{
	size_t			go_front;
	char			*after;
	char			*before;
	char			*concat;

	while (itf_reg->vector->size <
			(ft_vctlen(itf_reg->vector) + ft_vctlen(itf_reg->clipboard) + 2))
		ft_vctrescale(itf_reg->vector);

	if (itf_reg->vector->buffer[itf_reg->window->cursor_index] != '\0')
	{
		before = ft_strsub(itf_reg->vector->buffer,
				0, itf_reg->window->cursor_index);
		after = ft_strsub(itf_reg->vector->buffer,
				itf_reg->window->cursor_index, ft_vctlen(itf_reg->vector));
		itf_reg->window->cursor_index = tc_ak_home(itf_reg);
		ft_bzero(itf_reg->vector->buffer, itf_reg->vector->size);
		concat = NULL;
		ft_asprintf(&concat, "%s%s%s",
				before, itf_reg->clipboard->buffer, after);
		ft_strncpy(itf_reg->vector->buffer, concat, ft_strlen(concat));
		redraw_input_line(itf_reg);
		go_front = ft_strlen(before) + ft_strlen(itf_reg->clipboard->buffer);
		while (go_front-- > 0)
			itf_reg->window->cursor_index = tc_ak_arrow_right(itf_reg);
		ft_strdel(&after);
		ft_strdel(&before);
		ft_strdel(&concat);
	}
	else
	{
//		ft_dprintf(2, "Pasting : %s\n", itf_reg->clipboard->buffer);
		print_words(itf_reg->clipboard->buffer, itf_reg);
		itf_reg->vector->buffer = ft_strcat(itf_reg->vector->buffer, itf_reg->clipboard->buffer);
	}
	return (itf_reg->window->cursor_index);
}

int		tc_ak_clear_screen(t_interface_registry *itf_reg)
{
	tputs(itf_reg->termcaps->clear, itf_reg->window->rows, ft_putc);
	itf_reg->window->x = 0;
	itf_reg->window->y = 0;
	print_words(PROMPT_TEXT, itf_reg);
	itf_reg->window->cursor_index = 0;
	itf_reg->window->cursor_index = redraw_input_line(itf_reg);
	itf_reg->window->cursor_index = tc_ak_end(itf_reg);
	return (itf_reg->window->cursor_index);
}

int		tc_ak_ctrl_down(t_interface_registry *itf_reg)
{
	size_t moves;
	size_t line_length;
	size_t lines_amount;

	moves = 0;
	line_length = (ft_vctlen(itf_reg->vector) - 1);
	lines_amount = ((line_length + PROMPT_TEXT_LENGTH) / itf_reg->window->cols) + 1;
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
	lines_amount = ((line_length + PROMPT_TEXT_LENGTH) / itf_reg->window->cols) + 1;
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
