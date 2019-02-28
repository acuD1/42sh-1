/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ctrl_ak.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/09 07:29:58 by skuppers          #+#    #+#             */
/*   Updated: 2019/02/28 14:59:53 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edit.h"

int		ak_keycodes[AK_AMOUNT][READ_SIZE];

void	init_ak_ctrl_up(void)
{
	ak_keycodes[AK_CTRL_UP][0] = 27;
	ak_keycodes[AK_CTRL_UP][1] = 91;
	ak_keycodes[AK_CTRL_UP][2] = 49;
	ak_keycodes[AK_CTRL_UP][3] = 59;
	ak_keycodes[AK_CTRL_UP][4] = 53;
	ak_keycodes[AK_CTRL_UP][5] = 65;
}
void	init_ak_ctrl_down(void)
{
	ak_keycodes[AK_CTRL_DOWN][0] = 27;
	ak_keycodes[AK_CTRL_DOWN][1] = 91;
	ak_keycodes[AK_CTRL_DOWN][2] = 49;
	ak_keycodes[AK_CTRL_DOWN][3] = 59;
	ak_keycodes[AK_CTRL_DOWN][4] = 53;
	ak_keycodes[AK_CTRL_DOWN][5] = 66;
}

void	init_ak_ctrl_left(void)
{
	ak_keycodes[AK_CTRL_LEFT][0] = 27;
	ak_keycodes[AK_CTRL_LEFT][1] = 91;
	ak_keycodes[AK_CTRL_LEFT][2] = 49;
	ak_keycodes[AK_CTRL_LEFT][3] = 59;
	ak_keycodes[AK_CTRL_LEFT][4] = 53;
	ak_keycodes[AK_CTRL_LEFT][5] = 68;
	ak_keycodes[AK_CTRL_LEFT][6] = 0;
}

void	init_ak_ctrl_right(void)
{
	ak_keycodes[AK_CTRL_RIGHT][0] = 27;
	ak_keycodes[AK_CTRL_RIGHT][1] = 91;
	ak_keycodes[AK_CTRL_RIGHT][2] = 49;
	ak_keycodes[AK_CTRL_RIGHT][3] = 59;
	ak_keycodes[AK_CTRL_RIGHT][4] = 53;
	ak_keycodes[AK_CTRL_RIGHT][5] = 67;
	ak_keycodes[AK_CTRL_RIGHT][6] = 0;
}

void	init_ak_ctrl_a(void)
{
	ak_keycodes[AK_CTRL_A][0] = 1;
	ak_keycodes[AK_CTRL_A][1] = 0;
}
void	init_ak_ctrl_e(void)
{
	ak_keycodes[AK_CTRL_E][0] = 5;
	ak_keycodes[AK_CTRL_E][1] = 0;
}

void	init_ak_ctrl_x(void)
{
	ak_keycodes[AK_CTRL_X][0] = 24;
	ak_keycodes[AK_CTRL_X][1] = 0;
}
void	init_ak_ctrl_b(void)
{
	ak_keycodes[AK_CTRL_B][0] = 2;
	ak_keycodes[AK_CTRL_B][1] = 0;
}
void	init_ak_ctrl_p(void)
{
	ak_keycodes[AK_CTRL_P][0] = 16;
	ak_keycodes[AK_CTRL_P][1] = 0;
}

void	init_ak_ctrl_rb(void)
{
	ak_keycodes[AK_CTRL_RB][0] = 27;
	ak_keycodes[AK_CTRL_RB][1] = 0;
}

void	init_ak_ctrl_lb(void)
{
	ak_keycodes[AK_CTRL_LB][0] = 29;
	ak_keycodes[AK_CTRL_LB][1] = 0;
}

void	init_ak_ctrl_r(void)
{
	ak_keycodes[AK_CTRL_R][0] = 18;
	ak_keycodes[AK_CTRL_R][1] = 0;
}

void	init_ak_ctrl_f(void)
{
	ak_keycodes[AK_CTRL_F][0] = 6;
	ak_keycodes[AK_CTRL_F][1] = 0;
}

void	init_ak_ctrl_l(void)
{
	ak_keycodes[AK_CTRL_L][0] = 12;
	ak_keycodes[AK_CTRL_L][1] = 0;
}
void	init_ak_ctrl_d(void)
{
	ak_keycodes[AK_CTRL_D][0] = 420;
	ak_keycodes[AK_CTRL_D][1] = 420;
	ak_keycodes[AK_CTRL_D][2] = 420;
}
void	init_ak_ctrl_c(void)
{
	ak_keycodes[AK_CTRL_C][0] = 420;
	ak_keycodes[AK_CTRL_C][1] = 420;
	ak_keycodes[AK_CTRL_C][2] = 420;
}
