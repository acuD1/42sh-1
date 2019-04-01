/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ctrl_ak.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/09 07:29:58 by skuppers          #+#    #+#             */
/*   Updated: 2019/04/01 13:58:30 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edit.h"

void	init_ak_ctrl_l(t_interface_registry *itf_reg)
{
	itf_reg->ak_keycodes[AK_CTRL_L][0] = 12;
	itf_reg->ak_keycodes[AK_CTRL_L][1] = 0;
}

void	init_ak_ctrl_d(t_interface_registry *itf_reg)
{
	itf_reg->ak_keycodes[AK_CTRL_D][0] = 4;
}
