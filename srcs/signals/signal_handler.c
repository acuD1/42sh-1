/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 16:25:47 by skuppers          #+#    #+#             */
/*   Updated: 2019/04/11 18:23:46 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "log.h"
#include "line_edit.h"

t_interface	*g_interface_registry_pointer;

void				redraw_prompt(int signo)
{
	(void)signo;
	t_interface *itf;

	itf = g_interface_registry_pointer;
	tc_ak_end(itf);

	if (signo != ft_atoi(INT_MAGIC_NUMBER))
		print_words("\n", itf);

	itf->cursor->x = 0;
	itf->cursor->y = 0;
	if (signo != ft_atoi(INT_MAGIC_NUMBER))
		ft_vctreset(itf->line);

	print_words(get_intern_var(itf->shell, itf->interface_state), itf);

	itf->cursor->index = 0;
}

static void				interface_resize_handler(int signo)
{
	struct 					winsize w;
	t_interface				*itf;

	(void)signo;
	if (ioctl(STDIN_FILENO, TIOCGWINSZ, &w) == -1)
	{
		ft_dprintf(2, "[ERROR] Terminal size could not be updated.\n");
		return ;
	}
	itf = g_interface_registry_pointer;

	init_window(itf->shell, itf);

	tputs(itf->termcaps->clear, 1, ft_putc);

	if ((itf->window->cols < (uint32_t)(ft_strlen(get_intern_var(itf->shell, INT_PS1)) * 2)
		|| itf->window->rows < 3) || ft_vctlen(itf->line) > (uint32_t)itf->window->max_chars)
		print_words("Terminal window size too small :-(", itf);
	else
	{
		redraw_prompt(ft_atoi(INT_MAGIC_NUMBER));
		redraw_input_line(itf);
		tc_ak_end(itf);
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
				t_interface *itf, t_registry *shell_registry)
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
