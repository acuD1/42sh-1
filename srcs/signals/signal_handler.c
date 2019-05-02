/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 16:25:47 by skuppers          #+#    #+#             */
/*   Updated: 2019/05/02 11:44:14 by skuppers         ###   ########.fr       */
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

	itf = &g_shell->interface;
	tc_ak_end(g_shell);
	if (signo != ft_atoi(INT_MAGIC_NUMBER))
		print_words(itf, "\n");
	itf->cursor.x = 0;
	itf->cursor.y = 0;
	if (signo != ft_atoi(INT_MAGIC_NUMBER))
		ft_vctreset(itf->line);
	itf->hist_ptr = NULL;
	print_words(itf, get_intern_var(g_shell, itf->state));
	itf->cursor.index = 0;
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
	itf = &g_shell->interface;
	init_window(g_shell);
	tputs(itf->termcaps.clear, 1, ft_putc);
	if ((itf->window.cols
			< (uint32_t)(ft_strlen(get_intern_var(g_shell, INT_PS1)) * 2)
		|| itf->window.rows < 3)
		|| ft_vctlen(itf->line) > (uint32_t)itf->window.max_chars)
		print_words(itf, "Terminal window size too small :-(");
	else
	{
		redraw_prompt(ft_atoi(INT_MAGIC_NUMBER));
		redraw_input_line(g_shell);
		tc_ak_end(g_shell);
	}
}

void			kill_process(int signo)
{
	t_job		*job;
	t_list		*proc;

	(void)signo;
	job = ((t_job*)(g_shell->current_job->data));
	proc = job->process_list;
	while (proc != NULL)
	{
		kill(((t_process*)(proc->data))->pid, SIGINT);
		proc = proc->next;
	}
}

static void		loop_signals(void (*func)(int))
{
	int i;

	i = 1;
	while (i < 32)
		signal(i++, func);
}

void			define_ign_signals(void)
{
	loop_signals(SIG_IGN);
}

void			define_parser_signals(void)
{
	loop_signals(SIG_IGN);
}

void			define_execution_signals(void)
{
	signal(SIGINT, kill_process);
}

void			define_interface_signals(void)
{
	signal(SIGWINCH, interface_resize_handler);
	signal(SIGINT, redraw_prompt);
}

void			define_default_signals(void)
{
	loop_signals(SIG_DFL);
}

int		define_runtime_signals(void)
{
	return (SUCCESS);
}
