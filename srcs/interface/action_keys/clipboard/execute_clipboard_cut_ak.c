/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_clipboard_cut_ak.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 10:41:35 by skuppers          #+#    #+#             */
/*   Updated: 2019/04/02 18:01:50 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edit.h"
#include "ft_printf.h"

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

int			tc_ak_cut_before_cursor(t_interface_registry *itf_reg)
{
	ft_bzero(itf_reg->clipboard->buffer, itf_reg->clipboard->size);
	while (itf_reg->clipboard->size < itf_reg->vector->size)
		ft_vctrescale(itf_reg->clipboard);
	itf_reg->clipboard->buffer = ft_strncpy(itf_reg->clipboard->buffer,
				itf_reg->vector->buffer, itf_reg->window->cursor_index);
	cut_vector(itf_reg->vector, itf_reg->window, 1);
	redraw_input_line(itf_reg);
	return (itf_reg->window->cursor_index);
}

int			tc_ak_cut_after_cursor(t_interface_registry *itf_reg)
{
	char *tmp;

	ft_bzero(itf_reg->clipboard->buffer, itf_reg->clipboard->size);
	while (itf_reg->clipboard->size < itf_reg->vector->size)
		ft_vctrescale(itf_reg->clipboard);
	tmp = ft_strsub(itf_reg->vector->buffer,
			itf_reg->window->cursor_index, ft_vctlen(itf_reg->vector));
	itf_reg->clipboard->buffer = ft_strcpy(itf_reg->clipboard->buffer, tmp);
	ft_strdel(&tmp);
	cut_vector(itf_reg->vector, itf_reg->window, -1);
	redraw_input_line(itf_reg);
	return (itf_reg->window->cursor_index);
}

int			tc_ak_cut_line(t_interface_registry *itf_reg)
{
	ft_bzero(itf_reg->clipboard->buffer, itf_reg->clipboard->size);
	while (itf_reg->clipboard->size < itf_reg->vector->size)
		ft_vctrescale(itf_reg->clipboard);
	itf_reg->clipboard->buffer = ft_strcpy(itf_reg->clipboard->buffer,
			itf_reg->vector->buffer);
	ft_bzero(itf_reg->vector->buffer, itf_reg->vector->size);
	redraw_input_line(itf_reg);
	return (itf_reg->window->cursor_index);
}
