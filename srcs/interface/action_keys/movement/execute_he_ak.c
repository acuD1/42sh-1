/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_he_ak.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 11:32:21 by skuppers          #+#    #+#             */
/*   Updated: 2019/04/09 19:16:32 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edit.h"
#include "ft_printf.h"

int	tc_ak_home(t_interface_registry *itf)
{
	if (validate_interface_content(itf) != 0)
		return (-1);
	while (itf->window->cursor > 0)
		tc_ak_arrow_left(itf);
	return (0);
}

int	tc_ak_end(t_interface_registry *itf)
{
	if (validate_interface_content(itf) != 0)
		return (-1);
	while (itf->window->cursor < ft_vctlen(itf->line))
		tc_ak_arrow_right(itf);
	return (0);
}
