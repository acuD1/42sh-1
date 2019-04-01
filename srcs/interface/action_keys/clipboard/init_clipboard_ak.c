/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_clipboard_ak.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 13:26:46 by skuppers          #+#    #+#             */
/*   Updated: 2019/04/01 13:27:03 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edit.h"

void	init_ak_ctrl_p(t_interface_registry *itf_reg)
{
	itf_reg->ak_keycodes[AK_CTRL_P][0] = 16;
	itf_reg->ak_keycodes[AK_CTRL_P][1] = 0;
}
