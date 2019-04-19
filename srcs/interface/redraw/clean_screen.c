/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_screen.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 11:51:44 by skuppers          #+#    #+#             */
/*   Updated: 2019/04/20 01:03:21 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edit.h"
#include "interface_functions.h"

uint32_t	clean_screen(t_registry *shell)
{
	t_interface	*itf;
	uint32_t	offset;
	uint32_t	clear_size;

	offset = 0;
	clear_size = 0;
	itf = &shell->interface;
	clear_size = (itf->window->max_chars < itf->line->size)
		? itf->window->max_chars : itf->line->size;
	tc_ak_home(shell);
	while (offset++ < clear_size)
		print_char(' ', itf);
	tc_ak_home(shell);
	return (itf->cursor->index);
}
