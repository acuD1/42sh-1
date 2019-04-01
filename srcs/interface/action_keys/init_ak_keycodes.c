/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ak_keycodes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 14:48:38 by skuppers          #+#    #+#             */
/*   Updated: 2019/04/01 19:34:55 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edit.h"

void	clean_ak_keycodes(t_interface_registry *itf_reg)
{
	int y;
	int x;

	y = 0;
	while (y < AK_AMOUNT)
	{
		x = 0;
		while (x < READ_SIZE)
		{
			itf_reg->ak_keycodes[y][x] = 0;
			++x;
		}
		++y;
	}
}

void	init_arrow_ak(t_interface_registry *itf_reg)
{
	init_ak_arrow_right(itf_reg);
	init_ak_arrow_left(itf_reg);
	init_ak_arrow_up(itf_reg);
	init_ak_arrow_down(itf_reg);
}

void	init_ctrl_ak(t_interface_registry *itf_reg)
{
	init_ak_ctrl_a(itf_reg);
	init_ak_ctrl_d(itf_reg);
	init_ak_ctrl_e(itf_reg);
	init_ak_ctrl_l(itf_reg);
	init_ak_ctrl_x(itf_reg);
	init_ak_ctrl_b(itf_reg);
	init_ak_ctrl_p(itf_reg);
	init_ak_ctrl_lb(itf_reg);
	init_ak_ctrl_rb(itf_reg);
	init_ak_ctrl_r(itf_reg);
	init_ak_ctrl_f(itf_reg);
	init_ak_ctrl_left(itf_reg);
	init_ak_ctrl_right(itf_reg);
	init_ak_ctrl_up(itf_reg);
	init_ak_ctrl_down(itf_reg);
}

void	init_special_ak(t_interface_registry *itf_reg)
{
	init_ak_enter(itf_reg);
	init_ak_home(itf_reg);
	init_ak_end(itf_reg);
	init_ak_backspace(itf_reg);
	init_ak_delete(itf_reg);
	init_ak_hightab(itf_reg);
}

void	init_ak_keycodes(t_interface_registry *itf_reg)
{
	itf_reg->ak_masks[AK_ARROW_RIGHT] = AK_ARROW_RIGHT_MASK;
	itf_reg->ak_masks[AK_ARROW_LEFT] = AK_ARROW_LEFT_MASK;
	itf_reg->ak_masks[AK_ARROW_UP] = AK_ARROW_UP_MASK;
	itf_reg->ak_masks[AK_ARROW_DOWN] = AK_ARROW_DOWN_MASK;
	itf_reg->ak_masks[AK_HOME] = AK_HOME_MASK;
	itf_reg->ak_masks[AK_END] = AK_END_MASK;
	itf_reg->ak_masks[AK_BACKSPACE] = AK_BACKSPACE_MASK;
	itf_reg->ak_masks[AK_DELETE] = AK_DELETE_MASK;
	itf_reg->ak_masks[AK_CTRL_A] = AK_CTRL_A_MASK;
	itf_reg->ak_masks[AK_CTRL_D] = AK_CTRL_D_MASK;
	itf_reg->ak_masks[AK_CTRL_E] = AK_CTRL_E_MASK;
	itf_reg->ak_masks[AK_CTRL_L] = AK_CTRL_L_MASK;
	itf_reg->ak_masks[AK_CTRL_X] = AK_CTRL_X_MASK;
	itf_reg->ak_masks[AK_CTRL_B] = AK_CTRL_B_MASK;
	itf_reg->ak_masks[AK_CTRL_P] = AK_CTRL_P_MASK;
	itf_reg->ak_masks[AK_CTRL_LB] = AK_CTRL_LB_MASK;
	itf_reg->ak_masks[AK_CTRL_RB] = AK_CTRL_RB_MASK;
	itf_reg->ak_masks[AK_CTRL_F] = AK_CTRL_F_MASK;
	itf_reg->ak_masks[AK_CTRL_R] = AK_CTRL_R_MASK;
	itf_reg->ak_masks[AK_CTRL_LEFT] = AK_CTRL_LEFT_MASK;
	itf_reg->ak_masks[AK_CTRL_RIGHT] = AK_CTRL_RIGHT_MASK;
	itf_reg->ak_masks[AK_TABULATION] = AK_TAB_MASK;
	itf_reg->ak_masks[AK_CTRL_DOWN] = AK_CTRL_DOWN_MASK;
	itf_reg->ak_masks[AK_CTRL_UP] = AK_CTRL_UP_MASK;
	itf_reg->ak_masks[AK_ENTER] = 0;
//	clean_ak_keycodes(itf_reg);
//	init_arrow_ak(itf_reg);
//	init_ctrl_ak(itf_reg);
//	init_special_ak(itf_reg);
}
