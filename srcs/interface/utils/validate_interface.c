/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_interface.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 17:08:16 by skuppers          #+#    #+#             */
/*   Updated: 2019/04/11 17:11:24 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edit.h"

int8_t		validate_interface_content(t_interface *itf)
{
	if (itf == NULL || itf->clip == NULL || itf->line == NULL
		|| itf->clip->buffer == NULL
		|| itf->line->buffer == NULL)
		return (-1);
	return (0);
}

