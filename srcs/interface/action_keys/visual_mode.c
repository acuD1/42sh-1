/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual_mode.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 15:44:54 by skuppers          #+#    #+#             */
/*   Updated: 2019/05/27 16:14:33 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include "interface_functions.h"

int8_t	ak_enter_visual_mode(t_registry *shell)
{
	shell->interface.visual_mode = TRUE;
	shell->interface.vis_start = shell->interface.cursor.index;
	shell->interface.vis_stop = shell->interface.cursor.index;
	return (SUCCESS);
}

int8_t	ak_exit_visual_mode(t_registry *shell)
{
	shell->interface.visual_mode = FALSE;
	set_redraw_flags(&shell->interface, RD_LINE);
	return (SUCCESS);
}
