/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_eof.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 10:42:28 by skuppers          #+#    #+#             */
/*   Updated: 2019/04/27 15:57:02 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "define.h"
#include <stdint.h>

uint8_t	is_eof(const char *buffer)
{
	if (buffer[0] == 4 && buffer[1] == '\0')
		return (TRUE);
	return (FALSE);
}
