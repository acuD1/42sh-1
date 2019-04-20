/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_termcap_strings.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 15:49:19 by skuppers          #+#    #+#             */
/*   Updated: 2019/04/20 04:56:03 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edit.h"
#include "interface_functions.h"
#include "log.h"

int				init_termcap_calls(t_registry *shell)
{
	if(!(shell->interface.termcaps.cs_down = ft_strdup(tgetstr("do", NULL))))
			return (-1);
	if(!(shell->interface.termcaps.cs_up = ft_strdup(tgetstr("up", NULL))))
		return (-1);
	if(!(shell->interface.termcaps.cs_left = ft_strdup(tgetstr("le", NULL))))
		return (-1);
	if(!(shell->interface.termcaps.cs_right = ft_strdup(tgetstr("nd", NULL))))
		return (-1);
	if(!(shell->interface.termcaps.clear = ft_strdup(tgetstr("cl", NULL))))
		return (-1);
	return (0);
}

void			init_termcap_actions(t_registry *shell)
{
	shell->interface.tc_call[AK_ARROW_LEFT] = &tc_ak_arrow_left;
	shell->interface.tc_call[AK_ARROW_RIGHT] = &tc_ak_arrow_right;
	shell->interface.tc_call[AK_ARROW_UP] = &tc_ak_arrow_up;
	shell->interface.tc_call[AK_ARROW_DOWN] = &tc_ak_arrow_down;
	shell->interface.tc_call[AK_HOME] = &tc_ak_home;
	shell->interface.tc_call[AK_END] = &tc_ak_end;
	shell->interface.tc_call[AK_BACKSPACE] = &tc_ak_backspace;
	shell->interface.tc_call[AK_DELETE] = &tc_ak_delete;
	shell->interface.tc_call[AK_CTRL_A] = &tc_ak_home;
	shell->interface.tc_call[AK_CTRL_D] = &tc_ak_ctrl_d;
	shell->interface.tc_call[AK_CTRL_E] = &tc_ak_end;
	shell->interface.tc_call[AK_CTRL_X] = &tc_ak_cut_line;
	shell->interface.tc_call[AK_CTRL_B] = &tc_ak_copy_line;
	shell->interface.tc_call[AK_CTRL_P] = &tc_ak_paste_clipboard;
	shell->interface.tc_call[AK_CTRL_L] = &tc_ak_clear_screen;
	shell->interface.tc_call[AK_CTRL_RB] = &tc_ak_copy_after_cursor;
	shell->interface.tc_call[AK_CTRL_LB] = &tc_ak_copy_before_cursor;
	shell->interface.tc_call[AK_CTRL_F] = &tc_ak_cut_before_cursor;
	shell->interface.tc_call[AK_CTRL_R] = &tc_ak_cut_after_cursor;
	shell->interface.tc_call[AK_CTRL_LEFT] = &tc_ak_prev_word;
	shell->interface.tc_call[AK_CTRL_RIGHT] = &tc_ak_next_word;
	shell->interface.tc_call[AK_TABULATION] = &tc_ak_hightab;
	shell->interface.tc_call[AK_CTRL_UP] = &tc_ak_ctrl_up;
	shell->interface.tc_call[AK_CTRL_DOWN] = &tc_ak_ctrl_down;
}
