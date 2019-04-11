/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_screen.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 11:51:44 by skuppers          #+#    #+#             */
/*   Updated: 2019/04/11 17:29:52 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edit.h"

uint32_t	clean_screen(t_interface *itf)
{
	uint32_t offset;
	uint32_t clear_size;

	offset = 0;
	clear_size = 0;
	clear_size = (itf->window->max_chars < itf->line->size)
		? itf->window->max_chars : itf->line->size;

	tc_ak_home(itf);
	while (offset++ < clear_size)
		print_char(' ', itf);
	tc_ak_home(itf);

	return (itf->cursor->index);
}
