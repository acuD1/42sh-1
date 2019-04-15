/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 15:41:22 by skuppers          #+#    #+#             */
/*   Updated: 2019/04/12 16:27:38 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edit.h"
#include "interface_functions.h"

int8_t	init_cursor(t_registry *shell)
{
	t_interface *itf;

	itf = shell->interface;
	itf->cursor->index = 0;
	itf->cursor->x = get_prompt_len(shell);
	itf->cursor->y = 0;
	return (0);
}
