/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_interface.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 17:08:16 by skuppers          #+#    #+#             */
/*   Updated: 2019/04/20 04:23:02 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

int8_t		validate_interface_content(t_interface *itf)
{
	if (itf == NULL || itf->clip == NULL || itf->line == NULL
		|| itf->clip->buffer == NULL
		|| itf->line->buffer == NULL)
		return (-1);
	return (0);
}
