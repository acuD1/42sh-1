/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_special_ak.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 15:14:28 by skuppers          #+#    #+#             */
/*   Updated: 2019/04/15 14:20:24 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edit.h"
#include "interface_functions.h"
#include "ft_printf.h"
#include "log.h"

int8_t		tc_ak_hightab(t_registry *shell)
{
	(void)shell;
	return (0);
}

int8_t		tc_ak_delete(t_registry *shell)
{
	if (validate_interface_content(shell->interface) != 0)
		return (-1);
	shift_content_left_once(shell->interface->line,
			shell->interface->cursor->index);
	redraw_after_cursor(shell);
	return (0);
}

int8_t		tc_ak_backspace(t_registry *shell)
{
	t_interface	*itf;

	itf = shell->interface;
	if (validate_interface_content(itf) != 0)
		return (-1);
	if (itf->cursor->index == 0)
		return (0);
	tc_ak_arrow_left(shell);
	shift_content_left_once(itf->line, itf->cursor->index);
	redraw_after_cursor(shell);
	return (0);
}
