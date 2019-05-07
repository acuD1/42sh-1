/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 16:25:47 by skuppers          #+#    #+#             */
/*   Updated: 2019/05/07 09:00:55 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"
#include <signal.h>
#include "interface_functions.h"
#include "sig.h"

void			define_ign_signals(void)
{
	loop_signals(SIG_IGN);
}

void			define_parser_signals(void)
{
	//loop_signals(SIG_IGN);
	signal(SIGINT, stop_parsing);
}

void			define_execution_signals(void)
{
	signal(SIGQUIT, exit_program);
	signal(SIGINT, kill_process);
	signal(SIGQUIT, kill_process);
}

void			define_interface_signals(void)
{
	signal(SIGQUIT, exit_program);
	signal(SIGWINCH, interface_resize_handler);
	signal(SIGINT, redraw_prompt);
}

void			define_default_signals(void)
{
	loop_signals(SIG_DFL);
}
