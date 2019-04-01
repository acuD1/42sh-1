/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_clipboard_copy_ak.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 13:25:01 by skuppers          #+#    #+#             */
/*   Updated: 2019/04/01 13:26:08 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edit.h"

void	init_ak_ctrl_b(t_interface_registry *itf_reg)
{
	itf_reg->ak_keycodes[AK_CTRL_B][0] = 2;
	itf_reg->ak_keycodes[AK_CTRL_B][1] = 0;
}

void	init_ak_ctrl_rb(t_interface_registry *itf_reg)
{
	itf_reg->ak_keycodes[AK_CTRL_RB][0] = 27;
	itf_reg->ak_keycodes[AK_CTRL_RB][1] = 0;
}

void	init_ak_ctrl_lb(t_interface_registry *itf_reg)
{
	itf_reg->ak_keycodes[AK_CTRL_LB][0] = 29;
	itf_reg->ak_keycodes[AK_CTRL_LB][1] = 0;
}
