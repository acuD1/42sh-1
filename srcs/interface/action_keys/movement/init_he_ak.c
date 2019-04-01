/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_he_ak.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 13:58:00 by skuppers          #+#    #+#             */
/*   Updated: 2019/04/01 13:59:49 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edit.h"

void	init_ak_ctrl_a(t_interface_registry *itf_reg)
{
	itf_reg->ak_keycodes[AK_CTRL_A][0] = 1;
	itf_reg->ak_keycodes[AK_CTRL_A][1] = 0;
}

void	init_ak_ctrl_e(t_interface_registry *itf_reg)
{
	itf_reg->ak_keycodes[AK_CTRL_E][0] = 5;
	itf_reg->ak_keycodes[AK_CTRL_E][1] = 0;
}

void	init_ak_home(t_interface_registry *itf_reg)
{
	itf_reg->ak_keycodes[AK_HOME][0] = 27;
	itf_reg->ak_keycodes[AK_HOME][1] = 91;
	itf_reg->ak_keycodes[AK_HOME][2] = 72;
}

void	init_ak_end(t_interface_registry *itf_reg)
{
	itf_reg->ak_keycodes[AK_END][0] = 27;
	itf_reg->ak_keycodes[AK_END][1] = 91;
	itf_reg->ak_keycodes[AK_END][2] = 70;
}


