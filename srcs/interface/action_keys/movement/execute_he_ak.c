/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_he_ak.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 11:32:21 by skuppers          #+#    #+#             */
/*   Updated: 2019/05/21 13:18:33 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <termcap.h>
#include "interface_functions.h"

int8_t	ak_home(t_registry *shell)
{
	set_redraw_flags(&shell->interface, RD_NONE | RD_CHOME);
	return (SUCCESS);
}

int8_t	ak_end(t_registry *shell)
{
	set_redraw_flags(&shell->interface, RD_NONE | RD_CEND);
	return (SUCCESS);
}
