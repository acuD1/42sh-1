/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_clipboard_cut_ak.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 10:41:35 by skuppers          #+#    #+#             */
/*   Updated: 2019/04/09 19:16:03 by skuppers         ###   ########.fr       */
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
		foobar = ft_strsub(vect->buffer, ws->cursor, ft_vctlen(vect));
		tmp = ft_strcpy(tmp, foobar);
		ft_strdel(&foobar);
	}
	else
		tmp = ft_strncpy(tmp, vect->buffer, ws->cursor);
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
			source->buffer, window->cursor);

		cut_vector(source, window, before);
	}
	else
	{
		tmp = ft_strsub(source->buffer, window->cursor, ft_vctlen(source));
		clipboard->buffer = ft_strcpy(clipboard->buffer, tmp);
		ft_strdel(&tmp);
		cut_vector(source, window, before);
	}
}

void move_buffer(char *dest, t_vector *source)
{
	ft_strcpy(dest, source->buffer);
	ft_bzero(source->buffer, source->size);
}

int			tc_ak_cut_before_cursor(t_interface_registry *itf)
{

	if (validate_interface_content(itf) != 0)
			return (-1);
	forge_vector(itf->clip, itf->line);
	copy_buffer_part(itf->clip, itf->line, itf->window, 1);
	redraw_input_line(itf);
	return (0);
}

int			tc_ak_cut_after_cursor(t_interface_registry *itf)
{

	if (validate_interface_content(itf) != 0)
			return (-1);
	forge_vector(itf->clip, itf->line);
	copy_buffer_part(itf->clip, itf->line, itf->window, 2);
	redraw_input_line(itf);
	return (0);
}

int			tc_ak_cut_line(t_interface_registry *itf)
{
	if (validate_interface_content(itf) != 0)
			return (-1);
	forge_vector(itf->clip, itf->line);
	move_buffer(itf->line->buffer, itf->line);
	redraw_input_line(itf);
	return (0);
}
