/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_special_ak.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 15:06:28 by skuppers          #+#    #+#             */
/*   Updated: 2019/03/01 11:08:46 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edit.h"


void	init_ak_hightab(t_interface_registry *itf_reg)
{
	itf_reg->ak_keycodes[AK_TABULATION][0] = 9;
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

void	init_ak_backspace(t_interface_registry *itf_reg)
{
	itf_reg->ak_keycodes[AK_BACKSPACE][0] = 127;
}

void	init_ak_delete(t_interface_registry *itf_reg)
{
	itf_reg->ak_keycodes[AK_DELETE][0] = 27;
	itf_reg->ak_keycodes[AK_DELETE][1] = 91;
	itf_reg->ak_keycodes[AK_DELETE][2] = 51;
	itf_reg->ak_keycodes[AK_DELETE][3] = 126;
}

void	init_ak_enter(t_interface_registry *itf_reg)
{
	itf_reg->ak_keycodes[AK_ENTER][0] = 10;
}
