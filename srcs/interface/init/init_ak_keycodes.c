/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ak_keycodes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 14:48:38 by skuppers          #+#    #+#             */
/*   Updated: 2019/03/01 17:38:35 by skuppers         ###   ########.fr       */
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

void	init_ak_keycodes(t_interface_registry *itf_reg)
{
	clean_ak_keycodes(itf_reg);
	init_ak_enter(itf_reg);
	init_ak_arrow_right(itf_reg);
	init_ak_arrow_left(itf_reg);
	init_ak_arrow_up(itf_reg);
	init_ak_arrow_down(itf_reg);
	init_ak_home(itf_reg);
	init_ak_end(itf_reg);
	init_ak_backspace(itf_reg);
	init_ak_delete(itf_reg);
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
	init_ak_hightab(itf_reg);
	init_ak_ctrl_up(itf_reg);
	init_ak_ctrl_down(itf_reg);
}
