/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_arrow_ak.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 15:12:56 by skuppers          #+#    #+#             */
/*   Updated: 2019/04/09 21:10:38 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edit.h"
#include "log.h"

int			tc_ak_arrow_right(t_interface_registry *itf)
{
	size_t	tmp_idx;

	if (validate_interface_content(itf) != 0)
		return (-1);

	tmp_idx = itf->window->cursor;
	if (tmp_idx < ft_vctlen(itf->line))
	{
		if (itf->window->x >= itf->window->cols - 1)
		{
			tputs(itf->termcaps->cs_down, 1, &ft_putc);
			tmp_idx = (tmp_idx + itf->window->cols);
			itf->window->y++;
			while (itf->window->x > 0)
			{
				--tmp_idx;
				itf->window->x--;
			}
		}
		else
		{
			tputs(itf->termcaps->cs_right, 1, &ft_putc);
			++tmp_idx;
			itf->window->x++;
		}
	}
	itf->window->cursor = tmp_idx;
	return (0);
}

static int		go_to_end_of_line(t_interface_registry *itf)
{
	while (itf->window->x < itf->window->cols)
	{
		tputs(itf->termcaps->cs_right, 1, &ft_putc);
		itf->window->x++;
	}
	itf->window->x--;
	return (0);
}

int			tc_ak_arrow_left(t_interface_registry *itf)
{
	size_t		prompt_length;
	size_t		tmp_idx;

	if (validate_interface_content(itf) != 0)
		return (-1);

	prompt_length = ft_strlen(get_intern_var(itf->sh_reg, itf->interface_state));

	tmp_idx = itf->window->cursor;
	if (tmp_idx >= 1)
	{
		if ((itf->window->x == 0 && itf->window->y >= 1))
		{
			tputs(itf->termcaps->cs_up, 1, &ft_putc);
			itf->window->y--;
			go_to_end_of_line(itf);
			--tmp_idx;
		}
		else
		{
			tputs(itf->termcaps->cs_left, 1, &ft_putc);
			--tmp_idx;
			itf->window->x--;
		}
	}
	itf->window->cursor = tmp_idx;
	return (0);
}

/*
** History placeholder
*/

int	tc_ak_arrow_up(t_interface_registry *itf)
{
	(void)itf;
	return (0);
}

/*
** History placeholder
*/

int		tc_ak_arrow_down(t_interface_registry *itf)
{
	(void)itf;
	return (0);
}
