/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc_vector.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 10:13:07 by skuppers          #+#    #+#             */
/*   Updated: 2019/04/27 15:57:14 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interface_functions.h"

void	realloc_vector(t_vector *dest, t_vector *source)
{
	while (dest->size < source->size)
		ft_vctrescale(dest);
	ft_bzero(dest->buffer, dest->size);
}

void	reset_vector(t_vector *line)
{
	ft_strdel(&(line->buffer));
	line->buffer = ft_strnew(16);
	line->size = 16;
}

void	replace_vector(t_vector *dest, t_vector *src)
{
	ft_strdel(&(dest->buffer));
	dest->buffer = ft_strdup(src->buffer);
	dest->size = ft_strlen(src->buffer);
	ft_strdel(&(src->buffer));
	free(src);
}

void	move_vector(t_vector *dest, char *src)
{
	ft_strdel(&(dest->buffer));
	dest->buffer = ft_strdup(src);
	dest->size = ft_strlen(src);
	free(src);
}
