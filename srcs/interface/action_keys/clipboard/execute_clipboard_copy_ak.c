/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_clip_copy_ak.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 10:40:38 by skuppers          #+#    #+#             */
/*   Updated: 2019/04/11 17:12:05 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edit.h"
#include "ft_printf.h"

void	forge_vector(t_vector *dest, t_vector *source)
{
	while (dest->size < source->size)
		ft_vctrescale(dest);
	ft_bzero(dest->buffer, dest->size);
}

int	tc_ak_copy_before_cursor(t_interface *itf)
{
	if (validate_interface_content(itf) != 0)
		return (-1);
	forge_vector(itf->clip, itf->line);
	itf->clip->buffer = ft_strncpy(itf->clip->buffer,
					itf->line->buffer, itf->cursor->index);
	return (0);
}

int	tc_ak_copy_after_cursor(t_interface *itf)
{
	char	*tmp;

	if (validate_interface_content(itf) != 0)
		return (-1);
	forge_vector(itf->clip, itf->line);
	tmp = ft_strsub(itf->line->buffer,
			itf->cursor->index, ft_vctlen(itf->line));
	itf->clip->buffer = ft_strcpy(itf->clip->buffer, tmp);
	ft_strdel(&tmp);
	return (0);
}

int	tc_ak_copy_line(t_interface *itf)
{
	if (validate_interface_content(itf) != 0)
		return (-1);
	forge_vector(itf->clip, itf->line);
	itf->clip->buffer = ft_strcpy(itf->clip->buffer, itf->line->buffer);
	return (0);
}
