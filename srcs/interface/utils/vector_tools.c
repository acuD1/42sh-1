/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 15:17:45 by skuppers          #+#    #+#             */
/*   Updated: 2019/02/08 11:33:43 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "line_edit.h"

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

void	shift_content_right_once(t_vector *vector, unsigned int cursor_index)
{
	if (cursor_index >= (vector->size - 2) || ft_strlen(vector->buffer) >= vector->size - 2)
		ft_vctrescale(vector);
	ft_strshift(vector->buffer, cursor_index, 1);
}

void	shift_content_left_once(t_vector *vector, unsigned int cursor_index)
{
	ft_strshift(vector->buffer, cursor_index, -1);
}
