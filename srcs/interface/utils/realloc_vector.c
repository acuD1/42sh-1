/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc_vector.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 10:13:07 by skuppers          #+#    #+#             */
/*   Updated: 2019/04/12 10:14:30 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edit.h"

void	realloc_vector(t_vector *dest, t_vector *source)
{
	while (dest->size < source->size)
		ft_vctrescale(dest);
	ft_bzero(dest->buffer, dest->size);
}
