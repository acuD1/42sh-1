/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redraw_prompt.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 09:08:59 by skuppers          #+#    #+#             */
/*   Updated: 2019/04/12 16:28:42 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "log.h"
#include "line_edit.h"
#include "interface_functions.h"

uint32_t		redraw_input_line(t_registry *shell)
{
	t_interface	*itf;
	uint32_t	offset;
	uint32_t	initial_cursor;

	itf = shell->interface;
	initial_cursor = itf->cursor->index;

	// do we need return value here?
	itf->cursor->index = clean_screen(shell);

	offset = 0;
	while (offset < ft_vctlen(itf->line))
		print_char(itf->line->buffer[offset++], itf);

	offset = 0;
	tc_ak_home(shell);
	while (offset++ < initial_cursor)
		tc_ak_arrow_right(shell);
	return (itf->cursor->index);
}

uint32_t		redraw_after_cursor(t_registry *shell)
{
	t_interface	*itf;
	uint32_t initial_cursor_pos;

	itf = shell->interface;
	initial_cursor_pos = itf->cursor->index;

	while (itf->cursor->index < itf->line->size
					&& itf->line->buffer[itf->cursor->index] != '\0')
		print_char(itf->line->buffer[itf->cursor->index], itf);
	print_char(' ', itf);
	while (itf->cursor->index > initial_cursor_pos
				&& itf->cursor->index >= 1)
		tc_ak_arrow_left(shell);
	return (itf->cursor->index);
}

uint32_t	replace_input_line(char *string, t_registry *shell)
{
	t_interface	*itf;
	uint32_t	index;

	index = 0;
	itf = shell->interface;
	itf->cursor->index = clean_screen(shell);

	ft_bzero(itf->line->buffer, itf->line->size);
	while (itf->line->size <= ft_strlen(string))
		ft_vctrescale(itf->line);
	itf->line->buffer = ft_strncpy(itf->line->buffer,
			string, ft_strlen(string));
	tc_ak_home(shell);

	print_words(string, itf);
	return (itf->cursor->index);
}
