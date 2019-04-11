/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_arrow_ak.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 15:12:56 by skuppers          #+#    #+#             */
/*   Updated: 2019/04/11 17:06:50 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edit.h"
#include "log.h"

static int		goto_endof_column(t_interface *itf)
{
	while (itf->cursor->x < itf->window->cols)
	{
		tputs(itf->termcaps->cs_right, 1, &ft_putc);
		itf->cursor->x++;
	}
	itf->cursor->x--;
	return (0);
}

int			tc_ak_arrow_right(t_interface *itf)
{
	if (validate_interface_content(itf) != 0)
		return (-1);
	if (itf->cursor->index < ft_vctlen(itf->line))
	{
		if (itf->cursor->x >= itf->window->cols - 1)
		{
			tputs(itf->termcaps->cs_down, 1, &ft_putc);
			itf->cursor->index += itf->window->cols;
			itf->cursor->y++;
			while (itf->cursor->x > 0)
			{
				itf->cursor->index--;
				itf->cursor->x--;
			}
		}
		else
		{
			tputs(itf->termcaps->cs_right, 1, &ft_putc);
			itf->cursor->index++;
			itf->cursor->x++;
		}
	}
	return (0);
}

int			tc_ak_arrow_left(t_interface *itf)
{
	uint32_t		prompt_length;

	if (validate_interface_content(itf) != 0)
		return (-1);
	prompt_length = get_prompt_len(itf);
	if (itf->cursor->index >= 1)
	{
		if ((itf->cursor->x == 0 && itf->cursor->y >= 1))
		{
			tputs(itf->termcaps->cs_up, 1, &ft_putc);
			itf->cursor->y--;
			goto_endof_column(itf);
			itf->cursor->index--;
		}
		else
		{
			tputs(itf->termcaps->cs_left, 1, &ft_putc);
			itf->cursor->index--;
			itf->cursor->x--;
		}
	}
	return (0);
}

/*
** History placeholder
*/

int	tc_ak_arrow_up(t_interface *itf)
{
	(void)itf;
	return (0);
}

/*
** History placeholder
*/

int		tc_ak_arrow_down(t_interface *itf)
{
	(void)itf;
	return (0);
}
