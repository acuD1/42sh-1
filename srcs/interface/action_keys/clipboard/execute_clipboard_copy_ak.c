/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_clip_copy_ak.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 10:40:38 by skuppers          #+#    #+#             */
/*   Updated: 2019/04/09 19:29:42 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edit.h"
#include "ft_printf.h"

int	validate_interface_content(t_interface_registry *itf)
{
	if (itf == NULL || itf->clip == NULL || itf->line == NULL
		|| itf->clip->buffer == NULL
		|| itf->line->buffer == NULL)
		return (-1);
	return (0);
}

void	forge_vector(t_vector *dest, t_vector *source)
{
	while (dest->size < source->size)
		ft_vctrescale(dest);
	ft_bzero(dest->buffer, dest->size);
}

int	tc_ak_copy_before_cursor(t_interface_registry *itf)
{
	if (validate_interface_content(itf) != 0)
		return (-1);
	forge_vector(itf->clip, itf->line);
	itf->clip->buffer = ft_strncpy(itf->clip->buffer,
					itf->line->buffer, itf->window->cursor);
	return (0);
}

int		tc_ak_copy_after_cursor(t_interface_registry *itf)
{
	char	*tmp;

	if (validate_interface_content(itf) != 0)
		return (-1);
	forge_vector(itf->clip, itf->line);
	tmp = ft_strsub(itf->line->buffer,
			itf->window->cursor, ft_vctlen(itf->line));
	itf->clip->buffer = ft_strcpy(itf->clip->buffer, tmp);
	ft_strdel(&tmp);
	return (0);
}

int	tc_ak_copy_line(t_interface_registry *itf)
{
	if (validate_interface_content(itf) != 0)
		return (-1);
	forge_vector(itf->clip, itf->line);
	itf->clip->buffer = ft_strcpy(itf->clip->buffer, itf->line->buffer);
	return (0);
}
