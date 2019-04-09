/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_clipboard_copy_ak.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 10:40:38 by skuppers          #+#    #+#             */
/*   Updated: 2019/04/08 12:24:22 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edit.h"
#include "ft_printf.h"

int		tc_ak_copy_before_cursor(t_interface_registry *itf_reg)
{
	if (itf_reg == NULL
			|| itf_reg->clipboard == NULL
			|| itf_reg->vector == NULL
			|| itf_reg->clipboard->buffer == NULL
			|| itf_reg->vector->buffer == NULL)
		return (0);

	if (!itf_reg || itf_reg->clipboard == NULL || itf_reg->vector == NULL)
		return (0);
	ft_bzero(itf_reg->clipboard->buffer, itf_reg->clipboard->size);
	while (itf_reg->clipboard->size < itf_reg->vector->size)
		ft_vctrescale(itf_reg->clipboard);
	itf_reg->clipboard->buffer = ft_strncpy(itf_reg->clipboard->buffer,
			itf_reg->vector->buffer, itf_reg->window->cursor_index);
	return (itf_reg->window->cursor_index);
}

int		tc_ak_copy_after_cursor(t_interface_registry *itf_reg)
{
	char	*tmp;

	if (itf_reg == NULL
			|| itf_reg->clipboard == NULL
			|| itf_reg->vector == NULL
			|| itf_reg->clipboard->buffer == NULL
			|| itf_reg->vector->buffer == NULL)
		return (0);

	ft_bzero(itf_reg->clipboard->buffer, itf_reg->clipboard->size);
	while (itf_reg->clipboard->size < itf_reg->vector->size)
		ft_vctrescale(itf_reg->clipboard);
	tmp = ft_strsub(itf_reg->vector->buffer,
			itf_reg->window->cursor_index, ft_vctlen(itf_reg->vector));
	itf_reg->clipboard->buffer = ft_strcpy(itf_reg->clipboard->buffer, tmp);
	ft_strdel(&tmp);
	return (itf_reg->window->cursor_index);
}

int		tc_ak_copy_line(t_interface_registry *itf_reg)
{
	if (itf_reg == NULL
			|| itf_reg->clipboard == NULL
			|| itf_reg->vector == NULL
			|| itf_reg->clipboard->buffer == NULL
			|| itf_reg->vector->buffer == NULL)
		return (0);

	ft_bzero(itf_reg->clipboard->buffer, itf_reg->clipboard->size);
	while (itf_reg->clipboard->size < itf_reg->vector->size)
		ft_vctrescale(itf_reg->clipboard);
	itf_reg->clipboard->buffer = ft_strcpy(itf_reg->clipboard->buffer,
			itf_reg->vector->buffer);
	return (itf_reg->window->cursor_index);
}
