/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vctnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 10:29:42 by skuppers          #+#    #+#             */
/*   Updated: 2019/02/08 11:34:35 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_vector	*ft_vctnew(size_t optional_size)
{
	t_vector	*new;
	char		*buffer;

	if (!(new = malloc(sizeof(t_vector))))
		return (NULL);

	if (optional_size > 0)
	{
		if (!(buffer = ft_strnew(optional_size)))
		{
			free(new);
			return (NULL);
		}
		new->size = optional_size;
	}
	else
	{
		if (!(buffer = ft_strnew(VECTOR_BUFFER_SIZE)))
		{
			free(new);
			return (NULL);
		}
		new->size = VECTOR_BUFFER_SIZE;
	}
	new->buffer = buffer;
	return (new);
}
