/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 16:25:47 by skuppers          #+#    #+#             */
/*   Updated: 2019/04/27 15:44:36 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "log.h"
#include "interface_functions.h"
#include <signal.h>

t_registry	*g_shell;

void			redraw_prompt(int signo)
{
	(void)signo;
	t_interface *itf;

	itf = g_shell->interface;
	tc_ak_end(g_shell);
	if (signo != ft_atoi(INT_MAGIC_NUMBER))
		print_words(itf, "\n");
	itf->cursor->x = 0;
	itf->cursor->y = 0;
	if (signo != ft_atoi(INT_MAGIC_NUMBER))
		ft_vctreset(itf->line);
	itf->hist_ptr = NULL;
	// check sub_prompt print
	// use a ps5 for pipes, if then, etc...
	print_words(itf, get_intern_var(g_shell, itf->state));
	itf->cursor->index = 0;
}

static void		interface_resize_handler(int signo)
{
	struct 					winsize w;
	t_interface				*itf;

	(void)signo;
	if (ioctl(STDIN_FILENO, TIOCGWINSZ, &w) == FAILURE)
	{
		ft_dprintf(2, "[ERROR] Terminal size could not be updated.\n");
		return ;
	}
	itf = g_shell->interface;
	init_window(g_shell, NULL);
	tputs(itf->termcaps->clear, 1, ft_putc);
	if ((itf->window->cols
			< (uint32_t)(ft_strlen(get_intern_var(g_shell, INT_PS1)) * 2)
		|| itf->window->rows < 3)
		|| ft_vctlen(itf->line) > (uint32_t)itf->window->max_chars)
		print_words(itf, "Terminal window size too small :-(");
	else
	{
		redraw_prompt(ft_atoi(INT_MAGIC_NUMBER));
		redraw_input_line(g_shell);
		tc_ak_end(g_shell);
	}
}

void			define_interface_default_signals(t_registry *sh_reg)
{
	if (signal(SIGWINCH, SIG_DFL) == SIG_ERR)
		log_print(sh_reg, LOG_ERROR, "Error catching the resize signal.\n");
	if (signal(SIGINT, SIG_DFL) == SIG_ERR)
		log_print(sh_reg, LOG_ERROR, "Error catching C-c\n");
}

void			define_interface_signal_behavior(t_registry *shell)
{
	g_shell = shell;
	if (signal(SIGWINCH, interface_resize_handler) == SIG_ERR)
		log_print(shell, LOG_ERROR,
						"Error catching the resize signal.\n");
	if (signal(SIGINT, redraw_prompt) == SIG_ERR)
		log_print(shell, LOG_ERROR, "Error catching C-c\n");
}

int		define_runtime_signals(void)
{
	return (SUCCESS);
}
