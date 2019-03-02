/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redraw_prompt.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 09:08:59 by skuppers          #+#    #+#             */
/*   Updated: 2019/03/02 17:18:33 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edit.h"
#include "ft_printf.h"
#include "log.h"
#include "libft.h"

static void print_char(char d, t_interface_registry *itf_reg)
{
	if (itf_reg->window->x == itf_reg->window->cols)
	{
		tputs(itf_reg->termcaps->cs_down, 1, &ft_putc);
		itf_reg->window->x = 0;
		itf_reg->window->y++;
	}
	write(1, &d, 1);
	itf_reg->window->cursor_index++;
	itf_reg->window->x++;
}

void	print_words(char *str, t_interface_registry *itf_reg)
{
	size_t i;

	i = 0;
	while (i < ft_strlen(str))
		print_char(str[i++], itf_reg);
}

int		redraw_input_line(t_interface_registry *itf_reg)
{
	size_t	i;
	size_t	initial_cursor_index;

	i = 0;
	initial_cursor_index = itf_reg->window->cursor_index;
	itf_reg->window->cursor_index = tc_ak_home(itf_reg);
	while (i++ < itf_reg->vector->size + 2)
		print_char(' ', itf_reg);
	itf_reg->window->cursor_index = tc_ak_home(itf_reg);
	i = 0;
	while (i < ft_vctlen(itf_reg->vector))
		print_char(itf_reg->vector->buffer[i++], itf_reg);
	itf_reg->window->cursor_index = tc_ak_home(itf_reg);
	i = 0;
	while (i < initial_cursor_index && i++ < ft_vctlen(itf_reg->vector))
		itf_reg->window->cursor_index =
			tc_ak_arrow_right(itf_reg);
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
}
