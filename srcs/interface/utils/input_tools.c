/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_printable.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 12:45:03 by skuppers          #+#    #+#             */
/*   Updated: 2019/04/12 16:29:00 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edit.h"
#include "interface_functions.h"

uint8_t		is_printable(char c[READ_SIZE])
{
	if (c[1] == 0 && ft_isprint(c[0]))
		return (1);
	return (0);
}

uint64_t	compute_mask(char c[READ_SIZE])
{
	unsigned short 	shift;
	unsigned short 	index;
	unsigned long 	value;
	unsigned long 	tmp;

	shift = 56;
	index = 0;
	value = 0;
	tmp = 0;
	while (index < 8 && c[index] != 0)
	{
		tmp = c[index++];
		tmp <<= shift;
		value |= tmp;
		shift -= 8;
	}
	return (value);
}

