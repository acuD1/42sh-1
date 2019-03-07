/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redraw_prompt.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 09:08:59 by skuppers          #+#    #+#             */
/*   Updated: 2019/03/07 19:27:37 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edit.h"
#include "ft_printf.h"
#include "log.h"
#include "libft.h"

static void print_char(char d, t_interface_registry *itf_reg)
{
	write(1, &d, 1);
	itf_reg->window->cursor_index++;
	itf_reg->window->x++;

	if (itf_reg->window->x == itf_reg->window->cols)
	{
		tputs(itf_reg->termcaps->cs_down, 1, &ft_putc);
		itf_reg->window->x = 0;
		itf_reg->window->y++;
	}

}
/* ONLY USE FOR PRINTING THE PS1 TEXT */
void	print_words(char *str, t_interface_registry *itf_reg)
{
	size_t i;

	i = 0;
	while (i < ft_strlen(str))
		print_char(str[i++], itf_reg);
}

int		redraw_input_line(t_interface_registry *itf_reg)
{
	size_t	offset;
	size_t	initial_cursor_index;

	offset = 0;
	initial_cursor_index = itf_reg->window->cursor_index;

	itf_reg->window->cursor_index = tc_ak_home(itf_reg);
	while (offset++ < ft_vctlen(itf_reg->vector) + 1)
		print_char(' ', itf_reg);

	itf_reg->window->cursor_index = tc_ak_home(itf_reg);

//	ft_dprintf(2, "Offset:%d | Len:%d\n", offset, ft_vctlen(itf_reg->vector));
//	if ((int)offset >= itf_reg->window->max_line_len)
//	{
//		print_words(START_OVERSIZE, itf_reg);
//		offset =
//(ft_vctlen(itf_reg->vector) - (itf_reg->window->max_line_len - OVERSIZE_LENGTH)) + 2;
//	}
//	else
//	ft_dprintf(2, "Cols:%d Rows:%d MaxLen:%d Len:%d Offset:%d\n", itf_reg->window->cols, itf_reg->window->rows, itf_reg->window->max_line_len, ft_vctlen(itf_reg->vector), offset);

	offset = 0;
	while (offset < ft_vctlen(itf_reg->vector))
		print_char(itf_reg->vector->buffer[offset++], itf_reg);

	itf_reg->window->cursor_index = tc_ak_home(itf_reg);

	offset = 0;
	while (offset < initial_cursor_index && offset++ < ft_vctlen(itf_reg->vector))
//			&& (int)offset++ < itf_reg->window->max_line_len - 2)
		itf_reg->window->cursor_index = tc_ak_arrow_right(itf_reg);

	return (itf_reg->window->cursor_index);
}

int		replace_input_line(char	*string, t_interface_registry *itf_registry)
{
	size_t index;

	index = 0;
	while (itf_registry->vector->buffer[index] != '\0')
	{
		itf_registry->vector->buffer[index] = ' ';
		++index;
	}
	itf_registry->window->cursor_index = redraw_input_line(itf_registry);
	ft_bzero(itf_registry->vector->buffer, itf_registry->vector->size);
	while (itf_registry->vector->size <= ft_strlen(string))
		ft_vctrescale(itf_registry->vector);

	itf_registry->vector->buffer = ft_strncpy(itf_registry->vector->buffer,
			string, ft_strlen(string));

	itf_registry->window->cursor_index = tc_ak_home(itf_registry);
	print_words(string, itf_registry);

	return (itf_registry->window->cursor_index);
}
/*
int		redraw_after_cursor(t_interface_registry *itf_reg)
{
	size_t index;
	size_t initial_cursor_pos;

	initial_cursor_pos = itf_reg->window->cursor_index;
	index = initial_cursor_pos;
	while (index < itf_reg->vector->size && itf_reg->vector->buffer[index] != '\0')
	{
		print_char(itf_reg->vector->buffer[index], itf_reg);
		++index;
	}
	print_char(' ', itf_reg);
	++index;
	while (index > initial_cursor_pos)
	{
		itf_reg->window->cursor_index = tc_ak_arrow_left(itf_reg);
		--index;
	}
	return (itf_reg->window->cursor_index);
}*/
