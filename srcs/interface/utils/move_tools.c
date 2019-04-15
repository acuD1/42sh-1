/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 13:26:46 by skuppers          #+#    #+#             */
/*   Updated: 2019/04/11 17:26:46 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edit.h"

static int8_t	only_whitespaces_after(char *str, uint32_t index, char direction)
{
		uint32_t idx;

		idx = index;
		if (direction > 0)
		{
			while (str[idx] != '\0' && str[idx] != ' ')
				++idx;
			while (str[idx] != '\0')
				if (str[idx++] != ' ')
					return (0);
		}
		else
		{
			while (idx > 0 && str[idx] != ' ')
				--idx;
			while (idx > 0)
				if (str[idx--] != ' ')
					return (0);
		}
		return (1);
}

uint32_t		get_next_char(char *str, uint32_t index, char direction)
{
	if (only_whitespaces_after(str, index, direction))
		return (index);

	if (direction > 0)
	{
		while (str[index] != '\0' && str[index] != ' ')
			++index;
		while (str[index] != '\0' && str[index] == ' ')
			++index;
	}
	else
	{
		while (index > 0 && str[index] != ' ')
			--index;
		while (index > 0 && str[index] == ' ')
			--index;
		while (index - 1 > 0 && str[index - 1] != ' ')
			--index;
	}
	return (index);
}
