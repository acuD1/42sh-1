/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 13:38:46 by skuppers          #+#    #+#             */
/*   Updated: 2019/04/04 13:30:16 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "log.h"
#include "line_edit.h"

t_winsize	*init_win_struct(t_registry *reg, t_interface_registry *itf)
{
	struct winsize	w;

	if (ioctl(STDIN_FILENO, TIOCGWINSZ, &w) == -1)
	{
		log_print(reg, LOG_ERROR, "Terminal size could not be determined!\n");
		return (NULL);
	}
	itf->window->cursor_index = 0;
	itf->window->x = ft_strlen(get_intern_var(reg, itf->interface_state));
	itf->window->y = 0;
	if (w.ws_col < 0)
		itf->window->cols = 0;
	else
		itf->window->cols = w.ws_col;

	add_internal_nbr(reg, INT_COLS, itf->window->cols);

	if (w.ws_row < 0)
		itf->window->rows = 0;
	else
		itf->window->rows = w.ws_row;

	add_internal_nbr(reg, INT_ROWS, itf->window->rows);

	itf->window->max_line_len =
		((itf->window->cols * itf->window->rows)
		 - (ft_atoi(get_intern_var(reg, INT_PS1)) + 3));
	return (itf->window);
}
