/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 13:38:46 by skuppers          #+#    #+#             */
/*   Updated: 2019/04/27 15:48:01 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "log.h"
#include "interface_functions.h"

int8_t	init_window(t_registry *shell, t_window *window)
{
	struct winsize	w;
	t_window		*win;

	if (window == NULL)
	{
		ft_memset(&win, 0, sizeof(t_window));
		*window = win;
	}
	if (ioctl(STDIN_FILENO, TIOCGWINSZ, &w) == -1)
	{
		log_print(shell, LOG_ERROR, "Terminal size could not be determined!\n");
		return (FAILURE);
	}
	window->rows = (w.ws_row <= 0) ? 0 : w.ws_row;
	window->cols = (w.ws_col <= 0) ? 0 : w.ws_col;
	if (add_internal_nbr(shell, INT_COLS, window->cols) == FAILURE)
		return (FAILURE);
	if (add_internal_nbr(shell, INT_ROWS, window->rows) == FAILURE)
		return (FAILURE);
	window->max_chars = ((window->cols * window->rows)
								- get_prompt_len(shell));
	return (SUCCESS);
}
