/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_termcap_strings.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 15:49:19 by skuppers          #+#    #+#             */
/*   Updated: 2019/04/09 19:13:09 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "log.h"
#include "line_edit.h"

static int		load_termcap(t_termcaps *termcp, char *str)
{
	char *cpy;

	if ((cpy = ft_strdup(tgetstr(str, NULL))) == NULL)
		return (0);
	if (ft_strequ(str, "im"))
		termcp->begin_insertion = cpy;
	else if (ft_strequ(str, "ei"))
		termcp->end_insertion = cpy;
	else if (ft_strequ(str, "do"))
		termcp->cs_down = cpy;
	else if (ft_strequ(str, "up"))
		termcp->cs_up = cpy;
	else if (ft_strequ(str, "le"))
		termcp->cs_left = cpy;
	else if (ft_strequ(str, "nd"))
		termcp->cs_right = cpy;
	else if (ft_strequ(str, "cl"))
		termcp->clear = cpy;
	else
	{
		ft_strdel(&cpy);
		return (0);
	}
	return (1);
}

t_termcaps		*init_termcap_calls(t_registry *reg)
{
	unsigned int	valid_termcaps;
	t_termcaps		*termcp;

	if (!(termcp = malloc(sizeof(t_termcaps))))
	{
		log_print(reg, LOG_CRITICAL,
				"Could not allocate memory for termcap structure.\n");
		return (NULL);
	}
	ft_memset(termcp, 0, sizeof(t_termcaps));
	valid_termcaps = 0;
	valid_termcaps += load_termcap(termcp, "im");
	valid_termcaps += load_termcap(termcp, "ei");
	valid_termcaps += load_termcap(termcp, "do");
	valid_termcaps += load_termcap(termcp, "up");
	valid_termcaps += load_termcap(termcp, "le");
	valid_termcaps += load_termcap(termcp, "nd");
	valid_termcaps += load_termcap(termcp, "cl");
	log_print(reg, LOG_INFO, "%d/7 termcaps loaded.\n", valid_termcaps);
	return (termcp);
}

void			init_termcap_actions(
		int (*tc_call[AK_AMOUNT])(t_interface_registry *itf))
{
	tc_call[AK_ARROW_RIGHT] = &tc_ak_arrow_right;
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

int				setup_keycodes(t_interface_registry *itf)
{
	init_ak_keycodes(itf);
	return (0);
}

int				link_actions_to_keys(t_interface_registry *itf)
{
	init_termcap_actions(itf->tc_call);
	return (0);
}
