/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_arrow_ak.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 15:12:56 by skuppers          #+#    #+#             */
/*   Updated: 2019/04/15 10:44:20 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edit.h"
#include "interface_functions.h"
#include "log.h"

static void	goto_endof_column(t_interface *itf)
{
	while (itf->cursor->x < itf->window->cols)
	{
		tputs(itf->termcaps->cs_right, 1, &ft_putc);
		itf->cursor->x++;
	}
	itf->cursor->x--;
}

int8_t		tc_ak_arrow_right(t_registry *shell)
{
	if (validate_interface_content(shell->interface) != 0)
		return (-1);
	if (shell->interface->cursor->index >= ft_vctlen(shell->interface->line))
		return (-2);
	if (shell->interface->cursor->x >= shell->interface->window->cols - 1)
	{
		tputs(shell->interface->termcaps->cs_down, 1, &ft_putc);
		shell->interface->cursor->index += shell->interface->window->cols;
		shell->interface->cursor->y++;
		while (shell->interface->cursor->x > 0)
		{
			shell->interface->cursor->index--;
			shell->interface->cursor->x--;
		}
	}
	else
	{
		tputs(shell->interface->termcaps->cs_right, 1, &ft_putc);
		shell->interface->cursor->index++;
		shell->interface->cursor->x++;
	}
	return (0);
}

int8_t			tc_ak_arrow_left(t_registry *shell)
{
	if (validate_interface_content(shell->interface) != 0)
		return (-1);
	if (shell->interface->cursor->index < 1)
		return (-2);
	if ((shell->interface->cursor->x == 0 && shell->interface->cursor->y >= 1))
	{
		tputs(shell->interface->termcaps->cs_up, 1, &ft_putc);
		shell->interface->cursor->y--;
		goto_endof_column(shell->interface);
		shell->interface->cursor->index--;
	}
	else
	{
		tputs(shell->interface->termcaps->cs_left, 1, &ft_putc);
		shell->interface->cursor->index--;
		shell->interface->cursor->x--;
	}
	return (0);
}

/*
** History placeholder
*/

int8_t	tc_ak_arrow_up(t_registry *shell)
{
	(void)shell;
	return (0);
}

/*
** History placeholder
*/

int8_t		tc_ak_arrow_down(t_registry *shell)
{
	(void)shell;
	return (0);
}
