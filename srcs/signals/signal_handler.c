/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 16:25:47 by skuppers          #+#    #+#             */
/*   Updated: 2019/03/01 17:30:35 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "startup.h"
#include "libft.h"
#include "ft_printf.h"
#include "line_edit.h"
#include "log.h"
#include <sys/ioctl.h>

t_interface_registry	*g_interface_registry_pointer;

static void				redraw_prompt(int signo)
{
	(void)signo;
	t_interface_registry *itf_ptr;

	itf_ptr = g_interface_registry_pointer;
	itf_ptr->window->cursor_index = tc_ak_end(itf_ptr);

	print_words("\n", itf_ptr);
	itf_ptr->window->x = 0;
	itf_ptr->window->y = 0;
	print_words(PROMPT_TEXT, itf_ptr);
	itf_ptr->window->cursor_index = 0;
	itf_ptr->window->cursor_index = redraw_input_line(itf_ptr);
	itf_ptr->window->cursor_index = tc_ak_end(itf_ptr);
}

static void				interface_resize_handler(int signo)
{
	size_t					line_s;
	size_t					line_len;
	struct 					winsize w;
	t_interface_registry 	*itf_ptr;

	(void)signo;
	if (ioctl(STDIN_FILENO, TIOCGWINSZ, &w) == -1)
	{
		ft_printf_fd(2, "[ERROR ]Terminal size could not be updated.\n");
		return ;
	}
	itf_ptr = g_interface_registry_pointer;
	itf_ptr->window->rows = w.ws_row;
	itf_ptr->window->cols = w.ws_col;
	itf_ptr->window->x = 0;
	itf_ptr->window->y = 0;

	tputs(itf_ptr->termcaps->clear, w.ws_row - 1, ft_putc);
	line_len = (ft_vctlen(itf_ptr->vector) - 1);
	line_s = ((line_len + PROMPT_TEXT_LENGTH) / itf_ptr->window->cols) + 1;
	if (itf_ptr->window->cols < PROMPT_TEXT_LENGTH * 2
			|| itf_ptr->window->rows < (line_s + 5))
		print_words("Terminal window size too small.", itf_ptr);
	else
	{
		print_words(PROMPT_TEXT, itf_ptr);
		itf_ptr->window->cursor_index = 0;
		redraw_input_line(itf_ptr);
		itf_ptr->window->cursor_index = tc_ak_end(itf_ptr);
	}
}

void					define_interface_signal_behavior(t_interface_registry *itf_reg, t_registry *shell_registry)
{
	g_interface_registry_pointer = itf_reg;
	if (signal(SIGWINCH, interface_resize_handler) == SIG_ERR)
		log_print(shell_registry, LOG_ERROR, "Error catching the resize signal.\n");
	if (signal(SIGINT, redraw_prompt) == SIG_ERR)
		log_print(shell_registry, LOG_ERROR, "Error catching C-c\n");
}

int		define_runtime_signals(void)
{
	/*
	 *	Do some signals stuff here
	 */
	return (0);
}
