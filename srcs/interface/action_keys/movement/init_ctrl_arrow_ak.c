/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ctrl_arrow_ak.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 13:21:28 by skuppers          #+#    #+#             */
/*   Updated: 2019/04/01 13:28:38 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edit.h"

void	init_ak_ctrl_up(t_interface_registry *itf_reg)
{
	itf_reg->ak_keycodes[AK_CTRL_UP][0] = 27;
	itf_reg->ak_keycodes[AK_CTRL_UP][1] = 91;
	itf_reg->ak_keycodes[AK_CTRL_UP][2] = 49;
	itf_reg->ak_keycodes[AK_CTRL_UP][3] = 59;
	itf_reg->ak_keycodes[AK_CTRL_UP][4] = 53;
	itf_reg->ak_keycodes[AK_CTRL_UP][5] = 65;
}

void	init_ak_ctrl_down(t_interface_registry *itf_reg)
{
	itf_reg->ak_keycodes[AK_CTRL_DOWN][0] = 27;
	itf_reg->ak_keycodes[AK_CTRL_DOWN][1] = 91;
	itf_reg->ak_keycodes[AK_CTRL_DOWN][2] = 49;
	itf_reg->ak_keycodes[AK_CTRL_DOWN][3] = 59;
	itf_reg->ak_keycodes[AK_CTRL_DOWN][4] = 53;
	itf_reg->ak_keycodes[AK_CTRL_DOWN][5] = 66;
}

void	init_ak_ctrl_left(t_interface_registry *itf_reg)
{
	itf_reg->ak_keycodes[AK_CTRL_LEFT][0] = 27;
	itf_reg->ak_keycodes[AK_CTRL_LEFT][1] = 91;
	itf_reg->ak_keycodes[AK_CTRL_LEFT][2] = 49;
	itf_reg->ak_keycodes[AK_CTRL_LEFT][3] = 59;
	itf_reg->ak_keycodes[AK_CTRL_LEFT][4] = 53;
	itf_reg->ak_keycodes[AK_CTRL_LEFT][5] = 68;
}

void	init_ak_ctrl_right(t_interface_registry *itf_reg)
{
	itf_reg->ak_keycodes[AK_CTRL_RIGHT][0] = 27;
	itf_reg->ak_keycodes[AK_CTRL_RIGHT][1] = 91;
	itf_reg->ak_keycodes[AK_CTRL_RIGHT][2] = 49;
	itf_reg->ak_keycodes[AK_CTRL_RIGHT][3] = 59;
	itf_reg->ak_keycodes[AK_CTRL_RIGHT][4] = 53;
	itf_reg->ak_keycodes[AK_CTRL_RIGHT][5] = 67;
}
