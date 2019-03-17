/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_arrow_ak.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 15:12:56 by skuppers          #+#    #+#             */
/*   Updated: 2019/03/17 14:55:14 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edit.h"
#include "ft_printf.h"
#include "log.h"
#include "history.h"


int tc_ak_arrow_right(t_interface_registry *itf_reg)
{
	size_t	tmp_idx;

	tmp_idx = itf_reg->window->cursor_index;

	if (tmp_idx < ft_vctlen(itf_reg->vector))
	{
		if (itf_reg->window->x >= itf_reg->window->cols - 1)
		{
			tputs(itf_reg->termcaps->cs_down, 1, &ft_putc);
			tmp_idx = (tmp_idx + itf_reg->window->cols);
			itf_reg->window->y++;

			while (itf_reg->window->x > 0)
			{
				--tmp_idx;
				itf_reg->window->x--;
			}
		}
		else
		{
			tputs(itf_reg->termcaps->cs_right, 1 , &ft_putc);
			++tmp_idx;
			itf_reg->window->x++;
		}
	}
	return (tmp_idx);
}

int tc_ak_arrow_left(t_interface_registry *itf_reg)
{
	size_t		prompt_length;
	size_t		tmp_idx;


	prompt_length = (itf_reg->interface_state == PS1) ? PROMPT_TEXT_LENGTH: PS2_TEXT_LENGTH;
	tmp_idx = itf_reg->window->cursor_index;
	if (tmp_idx >= 1)
	{

		if ((itf_reg->window->x == 0 && itf_reg->window->y >= 1))// ||
		{
			tputs(itf_reg->termcaps->cs_up, 1, &ft_putc);
			itf_reg->window->y--;

			while (itf_reg->window->x < itf_reg->window->cols)
			{
				tputs(itf_reg->termcaps->cs_right, 1, &ft_putc);
				itf_reg->window->x++;
			}
			--tmp_idx;
			itf_reg->window->x--;
		}
		else if (itf_reg->window->y != 0)
		{
			tputs(itf_reg->termcaps->cs_left, 1, &ft_putc);
			--tmp_idx;
			itf_reg->window->x--;
		}
		else if (itf_reg->window->y == 0 && itf_reg->window->x > prompt_length)
		{
			tputs(itf_reg->termcaps->cs_left, 1, &ft_putc);
			--tmp_idx;
			itf_reg->window->x--;

		}
	}
	return (tmp_idx);
}

int tc_ak_arrow_up(t_interface_registry *itf_reg)
{
/*	if (itf_reg->history_head != NULL && itf_reg->history_ptr == NULL)
	{
		itf_reg->history_ptr = itf_reg->history_head;
		return (replace_input_line(itf_reg->history_ptr->command, itf_reg));
	}
	else
	{
		if (itf_reg->history_ptr != NULL && itf_reg->history_ptr->prev != NULL)
		{
			itf_reg->history_ptr = itf_reg->history_ptr->prev;
			return (replace_input_line(itf_reg->history_ptr->command, itf_reg));
		}
		return (itf_reg->window->cursor_index);
	}
*/
	return (itf_reg->window->cursor_index);
}

int tc_ak_arrow_down(t_interface_registry *itf_reg)
{
/*	if (itf_reg->history_ptr != NULL && itf_reg->history_ptr->next != NULL)
	{
		itf_reg->history_ptr = itf_reg->history_ptr->next;
		return (replace_input_line(itf_reg->history_ptr->command, itf_reg));
	}
	else if (itf_reg->history_ptr != NULL && itf_reg->history_ptr->next == NULL)
	{
		itf_reg->history_ptr = NULL;
		return (replace_input_line("", itf_reg));
	}
	*/
/*
	t_vector *vect = ft_vctnew(0);
	char *str = ft_strdup("abcdefghijklmnopqrstuvwxyz");

	int toshift = 3;

	vect->buffer = str;
	vect->size = ft_strlen(str);

	ft_dprintf(2, "Before |%s| len:%d\n", vect->buffer, ft_vctlen(vect));
	shift_content_right_once(vect, toshift);
	ft_dprintf(2, "After  |%s| len:%d\n", vect->buffer, ft_vctlen(vect));
	vect->buffer[toshift] = 'X';
	ft_dprintf(2, "After2 |%s| len:%d\n", vect->buffer, ft_vctlen(vect));
*/
	return (itf_reg->window->cursor_index);
}
