/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_arrow_ak.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 15:12:56 by skuppers          #+#    #+#             */
/*   Updated: 2019/02/27 15:20:25 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edit.h"
#include "ft_printf.h"
#include "log.h"
//#include "history.h"


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
	size_t		tmp_idx;

	tmp_idx = itf_reg->window->cursor_index;
	if (tmp_idx >= 1)
	{

		if (itf_reg->window->x == 0 && itf_reg->window->y >= 1)
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
		else
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
	return (itf_reg->window->cursor_index);
}

int tc_ak_arrow_down(t_interface_registry *itf_reg)
{
	return (itf_reg->window->cursor_index);
}
