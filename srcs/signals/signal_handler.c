/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 16:25:47 by skuppers          #+#    #+#             */
/*   Updated: 2019/04/09 19:15:49 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "log.h"
#include "line_edit.h"

t_interface_registry	*g_interface_registry_pointer;

void				redraw_prompt(int signo)
{
	(void)signo;
	t_interface_registry *itf_ptr;

	itf_ptr = g_interface_registry_pointer;
	tc_ak_end(itf_ptr);

	if (signo != ft_atoi(INT_MAGIC_NUMBER))
		print_words("\n", itf_ptr);

	itf_ptr->window->x = 0;
	itf_ptr->window->y = 0;
	if (signo != ft_atoi(INT_MAGIC_NUMBER))
		ft_vctreset(itf_ptr->line);

	print_words(get_intern_var(itf_ptr->sh_reg, itf_ptr->interface_state), itf_ptr);

	itf_ptr->window->cursor = 0;
}

static void				interface_resize_handler(int signo)
{
	struct 					winsize w;
	t_interface_registry 	*itf_ptr;

	(void)signo;
	if (ioctl(STDIN_FILENO, TIOCGWINSZ, &w) == -1)
	{
		ft_dprintf(2, "[ERROR] Terminal size could not be updated.\n");
		return ;
	}
	itf_ptr = g_interface_registry_pointer;
	itf_ptr->window->rows = w.ws_row;
	itf_ptr->window->cols = w.ws_col;
	itf_ptr->window->x = 0;
	itf_ptr->window->y = 0;
	itf_ptr->window->max_line_len =
		((itf_ptr->window->cols * itf_ptr->window->rows)
		 - (ft_strlen(get_intern_var(itf_ptr->sh_reg, INT_PS1)) + 3));

	tputs(itf_ptr->termcaps->clear, w.ws_row - 1, ft_putc);

	if ((itf_ptr->window->cols
		< (size_t)(ft_strlen(get_intern_var(itf_ptr->sh_reg, INT_PS1)) * 2)
		|| itf_ptr->window->rows < 3)
			|| ft_vctlen(itf_ptr->line) > (size_t)itf_ptr->window->max_line_len)
		print_words("Terminal window size too small :-(", itf_ptr);
	else
	{
		redraw_prompt(ft_atoi(INT_MAGIC_NUMBER));
		redraw_input_line(itf_ptr);
		tc_ak_end(itf_ptr);
	}
}

void					define_interface_default_signals(t_registry *sh_reg)
{
	if (signal(SIGWINCH, SIG_DFL) == SIG_ERR)
		log_print(sh_reg, LOG_ERROR, "Error catching the resize signal.\n");
	if (signal(SIGINT, SIG_DFL) == SIG_ERR)
		log_print(sh_reg, LOG_ERROR, "Error catching C-c\n");
}

void					define_interface_signal_behavior(
				t_interface_registry *itf, t_registry *shell_registry)
{
	g_interface_registry_pointer = itf;
	if (signal(SIGWINCH, interface_resize_handler) == SIG_ERR)
		log_print(shell_registry, LOG_ERROR,
						"Error catching the resize signal.\n");
	if (signal(SIGINT, redraw_prompt) == SIG_ERR)
		log_print(shell_registry, LOG_ERROR, "Error catching C-c\n");
}

int		define_runtime_signals(void)
{
	return (0);
}
