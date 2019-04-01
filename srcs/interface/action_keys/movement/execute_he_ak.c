/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_he_ak.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 11:32:21 by skuppers          #+#    #+#             */
/*   Updated: 2019/04/01 11:32:21 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edit.h"
#include "ft_printf.h"

int	tc_ak_home(t_interface_registry *itf_reg)
{
	while (itf_reg->window->cursor_index > 0)
		itf_reg->window->cursor_index = tc_ak_arrow_left(itf_reg);
	return (itf_reg->window->cursor_index);
}

int	tc_ak_end(t_interface_registry *itf_reg)
{
	while (itf_reg->window->cursor_index < (int)ft_vctlen(itf_reg->vector))
		itf_reg->window->cursor_index = tc_ak_arrow_right(itf_reg);
	return (itf_reg->window->cursor_index);
}
