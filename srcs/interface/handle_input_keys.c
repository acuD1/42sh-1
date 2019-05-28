/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input_keys.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 14:40:53 by skuppers          #+#    #+#             */
/*   Updated: 2019/05/28 11:21:59 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include "interface_functions.h"
#include "log.h"

static void		handle_printable_char(t_registry *shell, const char c)
{
	t_vector *line;
	t_cursor *cursor;

	line = shell->interface.line;
	cursor = &shell->interface.cursor;

	if (cursor->index == 0)
	{
		vct_push(line, c);
		set_redraw_flags(&shell->interface, RD_LINE | RD_CMOVE);
		set_cursor_pos(&shell->interface, 1);
	}
	else if (cursor->index == vct_len(line))
	{
		vct_add(line, c);
		set_redraw_flags(&shell->interface, RD_LAST | RD_CEND);
	}
	else
	{
		vct_insert_char(line, c, cursor->index);
		set_redraw_flags(&shell->interface, RD_LINE | RD_CMOVE);
//		set_redraw_bounds(&shell->interface, cursor->index, 0);
		set_cursor_pos(&shell->interface, cursor->index + 1);
	}
}

// May rework to put the computed masks into a hashmap
// assiocated with the function pointers
#include <stdio.h>
static void		handle_actionkey(t_registry *shell, char c[READ_SIZE])
{
	uint32_t	index;
	uint64_t	value;

	index = 0;
	value = compute_mask(c);
//	printf("Mask:%llu\n", value);
	(void)shell;
	while (index < AK_AMOUNT)
	{
		if (value == shell->interface.ak_masks[index])
			shell->interface.tc_call[index](shell);
		++index;
	}
}

void			handle_input_key(t_registry *shell, char c[READ_SIZE])
{
	if (is_printable(c))
		handle_printable_char(shell, c[0]);
	else
		handle_actionkey(shell, c);
}
