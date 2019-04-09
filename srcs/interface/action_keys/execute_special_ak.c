/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_special_ak.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 15:14:28 by skuppers          #+#    #+#             */
/*   Updated: 2019/04/09 19:19:48 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edit.h"
#include "ft_printf.h"

/*
**	Autocompletion
*/

int		tc_ak_hightab(t_interface_registry *itf)
{
	(void)itf;
	return (0);
}

int		tc_ak_delete(t_interface_registry *itf)
{
	if (validate_interface_content(itf) != 0)
		return (-1);

	shift_content_left_once(itf->line,
			itf->window->cursor);
	redraw_after_cursor(itf);
	return (0);
}

int		tc_ak_backspace(t_interface_registry *itf)
{
	if (validate_interface_content(itf) != 0)
		return (-1);

	if (itf->window->cursor >= 1)
	{
		tc_ak_arrow_left(itf);
		shift_content_left_once(itf->line, itf->window->cursor);
		redraw_after_cursor(itf);
	}
	return (0);
}
