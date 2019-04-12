/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_termcap_strings.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 15:49:19 by skuppers          #+#    #+#             */
/*   Updated: 2019/04/12 16:51:03 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "log.h"
#include "line_edit.h"
#include "interface_functions.h"

t_termcaps		*init_termcap_calls(t_registry *reg)
{
	t_termcaps		*termcp;

	if (!(termcp = malloc(sizeof(t_termcaps))))
	{
		log_print(reg, LOG_CRITICAL,
				"Could not allocate memory for termcap structure.\n");
		return (NULL);
	}
	ft_memset(termcp, 0, sizeof(t_termcaps));

	termcp->cs_down = ft_strdup(tgetstr("do", NULL));
	termcp->cs_up = ft_strdup(tgetstr("up", NULL));
	termcp->cs_left = ft_strdup(tgetstr("le", NULL));
	termcp->cs_right = ft_strdup(tgetstr("nd", NULL));
	termcp->clear = ft_strdup(tgetstr("cl", NULL));

	return (termcp);
}

void			init_termcap_actions(int8_t (*tc_call[AK_AMOUNT])(t_registry *shell))
{
	tc_call[AK_ARROW_LEFT] = &tc_ak_arrow_left;
	tc_call[AK_ARROW_UP] = &tc_ak_arrow_up;
	tc_call[AK_ARROW_DOWN] = &tc_ak_arrow_down;
	tc_call[AK_HOME] = &tc_ak_home;
	tc_call[AK_END] = &tc_ak_end;
	tc_call[AK_BACKSPACE] = &tc_ak_backspace;
	tc_call[AK_DELETE] = &tc_ak_delete;
	tc_call[AK_CTRL_A] = &tc_ak_home;
	tc_call[AK_CTRL_D] = &tc_ak_ctrl_d;
	tc_call[AK_CTRL_E] = &tc_ak_end;
	tc_call[AK_CTRL_X] = &tc_ak_cut_line;
	tc_call[AK_CTRL_B] = &tc_ak_copy_line;
	tc_call[AK_CTRL_P] = &tc_ak_paste_clipboard;
	tc_call[AK_CTRL_L] = &tc_ak_clear_screen;
	tc_call[AK_CTRL_RB] = &tc_ak_copy_after_cursor;
	tc_call[AK_CTRL_LB] = &tc_ak_copy_before_cursor;
	tc_call[AK_CTRL_F] = &tc_ak_cut_before_cursor;
	tc_call[AK_CTRL_R] = &tc_ak_cut_after_cursor;
	tc_call[AK_CTRL_LEFT] = &tc_ak_prev_word;
	tc_call[AK_CTRL_RIGHT] = &tc_ak_next_word;
	tc_call[AK_TABULATION] = &tc_ak_hightab;
	tc_call[AK_CTRL_UP] = &tc_ak_ctrl_up;
	tc_call[AK_CTRL_DOWN] = &tc_ak_ctrl_down;
}

void			setup_keycodes(t_interface *itf)
{
	init_ak_keycodes(itf);
}

void			link_actions_to_keys(t_registry *shell)
{
//	init_termcap_actions(&(shell->interface->tc_call));
	shell->interface->tc_call[AK_ARROW_RIGHT] = &tc_ak_arrow_right;
}
