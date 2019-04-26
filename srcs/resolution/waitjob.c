/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waitjob.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 14:02:11 by skuppers          #+#    #+#             */
/*   Updated: 2019/04/26 15:54:02 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"
#include "resolve.h"

int8_t		set_process_status(t_process *process, pid_t pid, int status)
{
	process->status = status;
	if (WIFSTOPPED(status))
		process->stopped = 1;
	else
	{
		process->completed = 1;
		if (WIFSIGNALED(status))
			ft_dprintf(2, "[ERROR] pid %d: Terminated by %d.\n"
			, pid, WTERMSIG(process->status));
	}
	return (0);
}

int8_t		update_process_status(pid_t pid, int status)
{
	t_list		*job;
	t_list		*process;

	if (pid <= 0)
		return (-1);
	// global job
	job = g_job_head;
	while (job)
	{
		process = ((t_job*)job->data)->f_process;
		while (process)
		{
			if (((t_process*)process->data)->pid == pid)
				return (set_process_status(((t_process*)process->data)
				, pid, status));
			process = process->next;
		}
		job = job->next;
	}
	ft_dprintf(2, "[WARNING]: No child process %d.\n", (int)pid);
	return (-1);
}

void		wait_for_job(t_job *job)
{
	int		status;
	pid_t	pid;

	pid = 0;
	pid = waitpid(WAIT_ANY, &status, WUNTRACED);
	while (!update_process_status(pid, status)
		&& !job_is_stopped(job)
		&& !job_is_completed(job))
		pid = waitpid(WAIT_ANY, &status, WUNTRACED);
}
