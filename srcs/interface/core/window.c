/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 13:38:46 by skuppers          #+#    #+#             */
/*   Updated: 2019/04/20 03:55:06 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "log.h"
#include "line_edit.h"
#include "interface_functions.h"

int8_t	init_window(t_registry *shell, t_interface *itf)
{
	struct winsize	w;

	if (ioctl(STDIN_FILENO, TIOCGWINSZ, &w) == -1)
	{
		log_print(shell, LOG_ERROR, "Terminal size could not be determined!\n");
		return (-1);
	}
	itf->window.rows = (w.ws_row <= 0) ? 0 : w.ws_row;
	itf->window.cols = (w.ws_col <= 0) ? 0 : w.ws_col;
	add_internal_nbr(shell, INT_COLS, itf->window.cols);
	add_internal_nbr(shell, INT_ROWS, itf->window.rows);
	itf->window.max_chars = ((itf->window.cols * itf->window.rows)
								- get_prompt_len(shell));
	return (0);
}
