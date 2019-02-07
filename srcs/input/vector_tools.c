/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 15:17:45 by skuppers          #+#    #+#             */
/*   Updated: 2019/02/07 15:08:41 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "line_edit.h"

size_t	vector_last_char(t_buffer *vector)
{
	size_t i;

	i = 0;
	while (i < vector->current_size && vector->buffer[i] != '\0')
		i++;
	return (i);
}

void vector_rescale(t_buffer *vector)
{
	char	*new;

	new = ft_strnew((vector->current_size) * BUFFER_SCALE_MULT);
	vector->current_size = vector->current_size * BUFFER_SCALE_MULT;
	ft_strcpy(new, vector->buffer);
	ft_strdel(&(vector->buffer));
	vector->buffer = new;
}

/**
 *	Be sure that str is big enough to store the string after shifting
 */
static void		ft_strshift(char *str, unsigned int index, int shift)
{
	size_t last;

	last = ft_strlen(str);
	if (shift == 0)
		return ;
	if (shift > 0)
	{
		while (last >= 1 && last >= index)
		{
			str[last + 1] = str[last];
			--last;
		}
	}
	else
	{
		while (index < last)
		{
			str[index] = str[index + 1];
			++index;
		}
		str[index] = '\0';
	}
}

void	shift_content_right_once(t_buffer *vector, unsigned int cursor_index)
{
	if (cursor_index >= (vector->current_size - 2) || ft_strlen(vector->buffer) >= vector->current_size - 2)
		vector_rescale(vector);
	ft_strshift(vector->buffer, cursor_index, 1);
}

void	shift_content_left_once(t_buffer *vector, unsigned int cursor_index)
{
	ft_strshift(vector->buffer, cursor_index, -1);
}
