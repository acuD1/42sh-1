/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 13:38:46 by skuppers          #+#    #+#             */
/*   Updated: 2019/04/02 18:29:51 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "log.h"
#include "line_edit.h"

t_winsize	*init_win_struct(t_registry *reg, t_winsize *window)
{
	struct winsize	w;

	if (ioctl(STDIN_FILENO, TIOCGWINSZ, &w) == -1)
	{
		log_print(reg, LOG_ERROR, "Terminal size could not be determined!\n");
		return (NULL);
	}
	window->cursor_index = 0;
	window->x = ft_atoi(get_intern_var(reg, INT_PS1_NAME));
	window->y = 0;
	if (w.ws_col < 0)
		window->cols = 0;
	else
		window->cols = w.ws_col;
	if (w.ws_row < 0)
		window->rows = 0;
	else
		window->rows = w.ws_row;
	window->max_line_len =
		((window->cols * window->rows)
		 - (ft_atoi(get_intern_var(reg, INT_PS1_NAME)) + 3));
	return (window);
}
