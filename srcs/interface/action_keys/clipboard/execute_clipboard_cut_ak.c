/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_clipboard_cut_ak.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 10:41:35 by skuppers          #+#    #+#             */
/*   Updated: 2019/04/08 15:33:37 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edit.h"
#include "ft_printf.h"

int	prepare_clipboard(t_vector *clipboard, t_vector *vector)
{
	ft_bzero(clipboard->buffer, clipboard->size);
	while (clipboard->size < vector->size)
		ft_vctrescale(clipboard);
	return (0);
}

static int	cut_vector(t_vector *vect, t_winsize *ws, int before)
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

void		copy_buffer_part(t_vector *clipboard, t_vector *source, t_winsize *window,
				int before)
{
	char *tmp;

	if (before > 0)
	{
		clipboard->buffer = ft_strncpy(clipboard->buffer,
			source->buffer, window->cursor_index);

		cut_vector(source, window, before);
	}
	else
	{
		tmp = ft_strsub(source->buffer, window->cursor_index, ft_vctlen(source));
		clipboard->buffer = ft_strcpy(clipboard->buffer, tmp);
		ft_strdel(&tmp);
		cut_vector(source, window, before);
	}
}

int			tc_ak_cut_before_cursor(t_interface_registry *itf_reg)
{
	if (itf_reg == NULL
			|| itf_reg->clipboard == NULL
			|| itf_reg->vector == NULL
			|| itf_reg->clipboard->buffer == NULL
			|| itf_reg->vector->buffer == NULL)
		return (0);

	prepare_clipboard(itf_reg->clipboard, itf_reg->vector);
	copy_buffer_part(itf_reg->clipboard, itf_reg->vector, itf_reg->window, 1);
	redraw_input_line(itf_reg);
	return (itf_reg->window->cursor_index);
}

int			tc_ak_cut_after_cursor(t_interface_registry *itf_reg)
{

	if (itf_reg == NULL
			|| itf_reg->clipboard == NULL
			|| itf_reg->vector == NULL
			|| itf_reg->clipboard->buffer == NULL
			|| itf_reg->vector->buffer == NULL)
		return (0);

	prepare_clipboard(itf_reg->clipboard, itf_reg->vector);
	copy_buffer_part(itf_reg->clipboard, itf_reg->vector, itf_reg->window, 2);
	redraw_input_line(itf_reg);
	return (itf_reg->window->cursor_index);
}

void move_buffer(char *dest, t_vector *source)
{
	ft_strcpy(dest, source->buffer);
	ft_bzero(source->buffer, source->size);
}
int			tc_ak_cut_line(t_interface_registry *itf_reg)
{
	if (itf_reg == NULL
			|| itf_reg->clipboard == NULL
			|| itf_reg->vector == NULL
			|| itf_reg->clipboard->buffer == NULL
			|| itf_reg->vector->buffer == NULL)
		return (0);

	prepare_clipboard(itf_reg->clipboard, itf_reg->vector);

	move_buffer(itf_reg->vector->buffer, itf_reg->vector);

	redraw_input_line(itf_reg);
	return (itf_reg->window->cursor_index);
}
