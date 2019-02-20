/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vctrescale.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 10:39:36 by skuppers          #+#    #+#             */
/*   Updated: 2019/02/08 10:44:39 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int		ft_vctrescale(t_vector *vector)
{
	char	*new;

	if (!(new = ft_strnew(vector->size * VECTOR_SCALE_MULT)))
		return (1);
	vector->size *= VECTOR_SCALE_MULT;
	ft_strcpy(new, vector->buffer);
	ft_strdel(&(vector->buffer));
	vector->buffer = new;
	return (0);
}
