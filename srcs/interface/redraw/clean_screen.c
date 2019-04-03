/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_screen.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 11:51:44 by skuppers          #+#    #+#             */
/*   Updated: 2019/04/03 10:25:52 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edit.h"

int	clean_screen(t_interface_registry *itf_reg)
{
	size_t offset;
	size_t clear_size;

	offset = 0;
	itf_reg->window->cursor_index = tc_ak_home(itf_reg);
	clear_size = ((size_t)itf_reg->window->max_line_len < itf_reg->vector->size)
		? itf_reg->window->max_line_len : itf_reg->vector->size;
	while (offset++ < clear_size)
		print_char(' ', itf_reg);
	itf_reg->window->cursor_index = tc_ak_home(itf_reg);
	return (itf_reg->window->cursor_index);
}
