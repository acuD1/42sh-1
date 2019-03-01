/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ctrl_ak.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/09 07:29:58 by skuppers          #+#    #+#             */
/*   Updated: 2019/03/01 16:07:29 by skuppers         ###   ########.fr       */
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

void	init_ak_ctrl_x(t_interface_registry *itf_reg)
{
	itf_reg->ak_keycodes[AK_CTRL_X][0] = 24;
	itf_reg->ak_keycodes[AK_CTRL_X][1] = 0;
}
void	init_ak_ctrl_b(t_interface_registry *itf_reg)
{
	itf_reg->ak_keycodes[AK_CTRL_B][0] = 2;
	itf_reg->ak_keycodes[AK_CTRL_B][1] = 0;
}
void	init_ak_ctrl_p(t_interface_registry *itf_reg)
{
	itf_reg->ak_keycodes[AK_CTRL_P][0] = 16;
	itf_reg->ak_keycodes[AK_CTRL_P][1] = 0;
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

void	init_ak_ctrl_l(t_interface_registry *itf_reg)
{
	itf_reg->ak_keycodes[AK_CTRL_L][0] = 12;
	itf_reg->ak_keycodes[AK_CTRL_L][1] = 0;
}
void	init_ak_ctrl_d(t_interface_registry *itf_reg)
{
	itf_reg->ak_keycodes[AK_CTRL_D][0] = 420;
	itf_reg->ak_keycodes[AK_CTRL_D][1] = 420;
	itf_reg->ak_keycodes[AK_CTRL_D][2] = 420;
}
void	init_ak_ctrl_c(t_interface_registry *itf_reg)
{
	itf_reg->ak_keycodes[AK_CTRL_C][0] = 420;
	itf_reg->ak_keycodes[AK_CTRL_C][1] = 420;
	itf_reg->ak_keycodes[AK_CTRL_C][2] = 420;
}
