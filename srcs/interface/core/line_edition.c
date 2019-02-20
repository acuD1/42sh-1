/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_edit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 14:41:16 by skuppers          #+#    #+#             */
/*   Updated: 2019/02/19 00:09:38 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edit.h"
#include "log.h"
#include "ft_printf.h"

int			ak_keycodes[AK_AMOUNT][READ_SIZE];
t_vector	*g_clipboard;

void	clean_ak_keycodes(void)
{
	int y;
	int x;

	y = 0;
	while (y < AK_AMOUNT)
	{
		x = 0;
		while (x < READ_SIZE)
		{
			ak_keycodes[y][x] = 0;
			++x;
		}
		++y;
	}
}

void	init_ak_keycodes(void)
{
	clean_ak_keycodes();
	init_ak_enter();
	init_ak_arrow_right();
	init_ak_arrow_left();
	init_ak_arrow_up();
	init_ak_arrow_down();
	init_ak_home();
	init_ak_end();
	init_ak_backspace();
	init_ak_delete();
	init_ak_ctrl_a();
	init_ak_ctrl_c();
	init_ak_ctrl_d();
	init_ak_ctrl_e();
	init_ak_ctrl_l();
	init_ak_ctrl_x();
	init_ak_ctrl_b();
	init_ak_ctrl_p();
	init_ak_ctrl_lb();
	init_ak_ctrl_rb();
	init_ak_ctrl_r();
	init_ak_ctrl_f();
	init_ak_ctrl_left();
	init_ak_ctrl_right();
}


