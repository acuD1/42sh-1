/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_screen.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 11:51:44 by skuppers          #+#    #+#             */
/*   Updated: 2019/04/09 21:02:41 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edit.h"

int	clean_screen(t_interface_registry *itf)
{
	size_t offset;
	size_t clear_size;

	offset = 0;
	tc_ak_home(itf);
	clear_size = ((size_t)itf->window->max_line_len < itf->line->size)
		? itf->window->max_line_len : itf->line->size;
	while (offset++ < clear_size)
		print_char(' ', itf);
	tc_ak_home(itf);
	return (itf->window->cursor);
}
