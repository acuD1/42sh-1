/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_signals.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 16:41:13 by skuppers          #+#    #+#             */
/*   Updated: 2019/05/05 16:45:45 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"
#include <signal.h>

void		kill_process(const int signo)
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

void		loop_signals(void (*func)(int))
{
	int signo;

	signo = 0;
	while (++signo < 32)
	{
		if (signo != SSIG_QUIT && signo != SSIG_STOP && signo != SSIG_KILL)
			signal(signo, func);
	}
}
