/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_special_ak.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 15:14:28 by skuppers          #+#    #+#             */
/*   Updated: 2019/04/12 15:57:24 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edit.h"
#include "interface_functions.h"
#include "ft_printf.h"
#include "log.h"

/*
**	Autocompletion
*/

int8_t		tc_ak_hightab(t_interface *itf)
{
	(void)itf;
	return (0);
}

int8_t		tc_ak_delete(t_interface *itf)
{
	if (validate_interface_content(itf) != 0)
		return (-1);

	shift_content_left_once(itf->line,
			itf->cursor->index);
	redraw_after_cursor(itf);
	return (0);
}

int8_t		tc_ak_backspace(t_interface *itf)
{
	if (validate_interface_content(itf) != 0)
		return (-1);

	if (itf->cursor->index == 0)
		return (0);

	int8_t le = tc_ak_arrow_left(itf);
	log_print(itf->shell, LOG_INFO, "left returned:%d\n", le);

	shift_content_left_once(itf->line, itf->cursor->index);
	redraw_after_cursor(itf);
	return (0);
}
