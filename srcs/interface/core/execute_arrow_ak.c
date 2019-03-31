/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_arrow_ak.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 15:12:56 by skuppers          #+#    #+#             */
/*   Updated: 2019/03/31 16:37:53 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edit.h"
#include "ft_printf.h"
#include "log.h"

int	tc_ak_arrow_right(t_interface_registry *itf_reg)
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
			tputs(itf_reg->termcaps->cs_right, 1, &ft_putc);
			++tmp_idx;
			itf_reg->window->x++;
		}
	}
	return (tmp_idx);
}

static void	go_to_end_of_line(t_interface_registry *itf_reg)
{
	while (itf_reg->window->x < itf_reg->window->cols)
	{
		tputs(itf_reg->termcaps->cs_right, 1, &ft_putc);
		itf_reg->window->x++;
	}
	itf_reg->window->x--;
}

int	tc_ak_arrow_left(t_interface_registry *itf_reg)
{
	size_t		prompt_length;
	size_t		tmp_idx;

	prompt_length =
		(itf_reg->interface_state == PS1)
		? PROMPT_TEXT_LENGTH : PS2_TEXT_LENGTH;
	tmp_idx = itf_reg->window->cursor_index;
	if (tmp_idx >= 1)
	{
		if ((itf_reg->window->x == 0 && itf_reg->window->y >= 1))
		{
			tputs(itf_reg->termcaps->cs_up, 1, &ft_putc);
			itf_reg->window->y--;
			go_to_end_of_line(itf_reg);
			--tmp_idx;
		}
		else
		{
			tputs(itf_reg->termcaps->cs_left, 1, &ft_putc);
			--tmp_idx;
			itf_reg->window->x--;
		}
	}
	return (tmp_idx);
}

int	tc_ak_arrow_up(t_interface_registry *itf_reg)
{
	/* History placeholder */
	return (itf_reg->window->cursor_index);
}

int	tc_ak_arrow_down(t_interface_registry *itf_reg)
{
	/* History placeholder */
	return (itf_reg->window->cursor_index);
}
