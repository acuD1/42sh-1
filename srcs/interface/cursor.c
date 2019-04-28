/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 15:41:22 by skuppers          #+#    #+#             */
/*   Updated: 2019/04/27 15:46:31 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interface_functions.h"

int8_t	init_cursor(t_registry *shell)
{
	t_cursor *ptr;

	ptr = shell->interface->cursor;
	cursor->index = 0;
	cursor->x = get_prompt_len(shell);
	cursor->y = 0;
	return (SUCCESS);
}
