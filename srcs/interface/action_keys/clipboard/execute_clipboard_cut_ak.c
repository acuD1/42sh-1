/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_clipboard_cut_ak.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 10:41:35 by skuppers          #+#    #+#             */
/*   Updated: 2019/04/11 17:18:14 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edit.h"
#include "ft_printf.h"

static int	cut_vector(t_vector *vect, t_cursor *cursor, int before)
{
	char	*tmp;
	char	*foobar;

	tmp = ft_strnew(vect->size);
	if (before > 0)
	{
		foobar = ft_strsub(vect->buffer, cursor->index, ft_vctlen(vect));
		tmp = ft_strcpy(tmp, foobar);
		ft_strdel(&foobar);
	}
	else
		tmp = ft_strncpy(tmp, vect->buffer, cursor->index);
	ft_strdel(&(vect->buffer));
	vect->buffer = tmp;
	return (0);
}

static void		copy_buffer_part(t_interface *itf, int8_t before)
{
	char *tmp;

	if (before > 0)
	{
		itf->clip->buffer = ft_strncpy(itf->clip->buffer, itf->line->buffer, itf->cursor->index);
		cut_vector(itf->line, itf->cursor, before);
	}
	else
	{
		tmp = ft_strsub(itf->line->buffer, itf->cursor->index, ft_vctlen(itf->line));
		itf->clip->buffer = ft_strcpy(itf->clip->buffer, tmp);
		ft_strdel(&tmp);
		cut_vector(itf->line, itf->cursor, before);
	}
}

void move_buffer(char *dest, t_vector *source)
{
	ft_strcpy(dest, source->buffer);
	ft_bzero(source->buffer, source->size);
}

int			tc_ak_cut_before_cursor(t_interface *itf)
{

	if (validate_interface_content(itf) != 0)
			return (-1);
	forge_vector(itf->clip, itf->line);
	copy_buffer_part(itf, 1);
	redraw_input_line(itf);
	return (0);
}

int			tc_ak_cut_after_cursor(t_interface *itf)
{

	if (validate_interface_content(itf) != 0)
			return (-1);
	forge_vector(itf->clip, itf->line);
	copy_buffer_part(itf, 2);
	redraw_input_line(itf);
	return (0);
}

int			tc_ak_cut_line(t_interface *itf)
{
	if (validate_interface_content(itf) != 0)
			return (-1);
	forge_vector(itf->clip, itf->line);
	move_buffer(itf->line->buffer, itf->line);
	redraw_input_line(itf);
	return (0);
}
