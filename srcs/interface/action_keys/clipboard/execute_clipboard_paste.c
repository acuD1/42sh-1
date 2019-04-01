/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_clipboard_ak.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 10:45:51 by skuppers          #+#    #+#             */
/*   Updated: 2019/04/01 10:47:05 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edit.h"
#include "ft_printf.h"

static int	insert_clipboard(t_interface_registry *itf_reg)
{
	int				length;
	char			*after;
	char			*before;
	char			*concat;

	length = 0;
	concat = NULL;
	before = NULL;
	after = NULL;
	before = ft_strsub(itf_reg->vector->buffer,
				0, itf_reg->window->cursor_index);
	after = ft_strsub(itf_reg->vector->buffer,
			itf_reg->window->cursor_index, ft_vctlen(itf_reg->vector));
	ft_asprintf(&concat, "%s%s%s",
			before, itf_reg->clipboard->buffer, after);
	ft_bzero(itf_reg->vector->buffer, itf_reg->vector->size);
	ft_strncpy(itf_reg->vector->buffer, concat, ft_strlen(concat));
	length = ft_strlen(before) + ft_strlen(itf_reg->clipboard->buffer);
	ft_strdel(&concat);
	ft_strdel(&after);
	ft_strdel(&before);
	return (length);
}

int			tc_ak_paste_clipboard(t_interface_registry *itf_reg)
{
	size_t			go_front;

	if ((ft_vctlen(itf_reg->clipboard) + ft_vctlen(itf_reg->vector))
			>= (size_t)itf_reg->window->max_line_len)
		return (itf_reg->window->cursor_index);
	while (itf_reg->vector->size < (ft_vctlen(itf_reg->vector)
				+ ft_vctlen(itf_reg->clipboard) + 2))
		ft_vctrescale(itf_reg->vector);
	if (itf_reg->vector->buffer[itf_reg->window->cursor_index] != '\0')
	{
		go_front = insert_clipboard(itf_reg);
		itf_reg->window->cursor_index = tc_ak_home(itf_reg);
		itf_reg->window->cursor_index = redraw_after_cursor(itf_reg);
		while (go_front-- > 0)
			itf_reg->window->cursor_index = tc_ak_arrow_right(itf_reg);
	}
	else
	{
		itf_reg->vector->buffer = ft_strcat(itf_reg->vector->buffer,
				itf_reg->clipboard->buffer);
		itf_reg->window->cursor_index = redraw_after_cursor(itf_reg);
		itf_reg->window->cursor_index = tc_ak_end(itf_reg);
	}
	return (itf_reg->window->cursor_index);
}
