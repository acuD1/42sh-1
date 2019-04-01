/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_clipboard_cut_ak.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 13:22:42 by skuppers          #+#    #+#             */
/*   Updated: 2019/04/01 13:24:13 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edit.h"

void	init_ak_ctrl_x(t_interface_registry *itf_reg)
{
	itf_reg->ak_keycodes[AK_CTRL_X][0] = 24;
	itf_reg->ak_keycodes[AK_CTRL_X][1] = 0;
}

void	init_ak_ctrl_r(t_interface_registry *itf_reg)
{
	itf_reg->ak_keycodes[AK_CTRL_R][0] = 18;
	itf_reg->ak_keycodes[AK_CTRL_R][1] = 0;
}

void	init_ak_ctrl_f(t_interface_registry *itf_reg)
{
	itf_reg->ak_keycodes[AK_CTRL_F][0] = 6;
	itf_reg->ak_keycodes[AK_CTRL_F][1] = 0;
}
