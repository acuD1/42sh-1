/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_eof.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 10:42:28 by skuppers          #+#    #+#             */
/*   Updated: 2019/04/27 14:30:16 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edit.h"

uint8_t	is_eof(char *buffer)
{
	if (buffer[0] == 4 && buffer[1] == '\0')
		return (TRUE);
	return (FALSE);
}

uint8_t is_only_whitespaces(char *buffer)
{
	char	*ptr;
	ptr = buffer;
	while (ptr)
	{
		if (*ptr != ' ')
			return (FALSE);
		++ptr;
	}
	return (TRUE);
}
