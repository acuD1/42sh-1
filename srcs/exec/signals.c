/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 12:38:03 by cempassi          #+#    #+#             */
/*   Updated: 2019/05/23 16:35:28 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "sig.h"
#include "21sh.h"
#include "interface_functions.h"
#include "resolve.h"
#include "exec.h"

void			signal_test(const int signo)
{
	(void)signo;
	g_shell->signal = 1;
}

void			signal_job(void)
{
	signal(SIGQUIT, exit_program);
	signal(SIGINT, kill_process);
	signal(SIGCHLD, signal_test);
	signal(SIGPIPE, kill_process);
}

void			signal_ignore(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGCHLD, SIG_IGN);
	signal(SIGSEGV, SIG_IGN);
	signal(SIGABRT, SIG_IGN);
	signal(SIGBUS, SIG_IGN);
}

void			signal_execution(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGCHLD, SIG_DFL);
	signal(SIGSEGV, SIG_DFL);
	signal(SIGABRT, SIG_DFL);
	signal(SIGBUS, SIG_DFL);
}
