/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ak.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 15:03:55 by skuppers          #+#    #+#             */
/*   Updated: 2019/03/01 11:04:07 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edit.h"

void	init_ak_arrow_right(t_interface_registry *itf_reg)
{
	itf_reg->ak_keycodes[AK_ARROW_RIGHT][0] = 27;
	itf_reg->ak_keycodes[AK_ARROW_RIGHT][1] = 91;
	itf_reg->ak_keycodes[AK_ARROW_RIGHT][2] = 67;
}

void	init_ak_arrow_left(t_interface_registry *itf_reg)
{
	itf_reg->ak_keycodes[AK_ARROW_LEFT][0] = 27;
	itf_reg->ak_keycodes[AK_ARROW_LEFT][1] = 91;
	itf_reg->ak_keycodes[AK_ARROW_LEFT][2] = 68;
}

void	init_ak_arrow_up(t_interface_registry *itf_reg)
{
	itf_reg->ak_keycodes[AK_ARROW_UP][0] = 27;
	itf_reg->ak_keycodes[AK_ARROW_UP][1] = 91;
	itf_reg->ak_keycodes[AK_ARROW_UP][2] = 65;
}

void	init_ak_arrow_down(t_interface_registry *itf_reg)
{
	itf_reg->ak_keycodes[AK_ARROW_DOWN][0] = 27;
	itf_reg->ak_keycodes[AK_ARROW_DOWN][1] = 91;
	itf_reg->ak_keycodes[AK_ARROW_DOWN][2] = 66;
}
