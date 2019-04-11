/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redraw_prompt.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 09:08:59 by skuppers          #+#    #+#             */
/*   Updated: 2019/04/11 17:29:48 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "log.h"
#include "line_edit.h"

void	print_char(char d, t_interface *itf)
{
	write(1, &d, 1);
	itf->cursor->index++;
	itf->cursor->x++;
	if (itf->cursor->x == itf->window->cols)
	{
		tputs(itf->termcaps->cs_down, 1, &ft_putc);
		itf->cursor->x = 0;
		itf->cursor->y++;
	}
}

void	print_words(char *str, t_interface *itf)
{
	uint32_t	i;

	i = 0;
	while (i < ft_strlen(str))
		print_char(str[i++], itf);
}

uint32_t		redraw_input_line(t_interface *itf)
{
	uint32_t	offset;
	uint32_t	initial_cursor;

	initial_cursor = itf->cursor->index;
	itf->cursor->index = clean_screen(itf);
	offset = 0;
	while (offset < ft_vctlen(itf->line))
		print_char(itf->line->buffer[offset++], itf);
	tc_ak_home(itf);
	offset = 0;
	while (offset++ < initial_cursor)
		tc_ak_arrow_right(itf);
	return (itf->cursor->index);
}

void		redraw_after_cursor(t_interface *itf)
{
	uint32_t index;
	uint32_t initial_cursor_pos;

	initial_cursor_pos = itf->cursor->index;
	index = initial_cursor_pos;
	while (index < itf->line->size
			&& itf->line->buffer[index] != '\0')
	{
		print_char(itf->line->buffer[index], itf);
		++index;
	}
	print_char(' ', itf);
	++index;
	while (index > initial_cursor_pos)
	{
		tc_ak_arrow_left(itf);
		--index;
	}
}

uint32_t	replace_input_line(char *string, t_interface *itf)
{
	uint32_t	index;

	index = 0;
	while (itf->line->buffer[index] != '\0')
	{
		itf->line->buffer[index] = ' ';
		++index;
	}
	itf->cursor->index = redraw_input_line(itf);
	ft_bzero(itf->line->buffer, itf->line->size);
	while (itf->line->size <= ft_strlen(string))
		ft_vctrescale(itf->line);
	itf->line->buffer = ft_strncpy(itf->line->buffer,
			string, ft_strlen(string));
	tc_ak_home(itf);
	print_words(string, itf);
	return (itf->cursor->index);
}
