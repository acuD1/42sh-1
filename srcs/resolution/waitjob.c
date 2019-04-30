/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waitjob.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 14:02:11 by skuppers          #+#    #+#             */
/*   Updated: 2019/04/30 13:56:35 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"
#include "resolve.h"

int8_t		set_process_status(t_process *process, pid_t pid, int status)
{
	process->status = status;
	if (WIFSTOPPED(status) != FALSE)
		process->stopped = 1;
	else
	{
		process->completed = 1;
		if (WIFSIGNALED(status) != FALSE)
		{
			ft_dprintf(2, "[WARNING] pid %d: Terminated by signo %d.\n"
							, pid, WTERMSIG(process->status));
			return (FAILURE);
		}

	}
	return (SUCCESS);
}

int8_t		update_process_status(pid_t pid, int status)
{
	t_list		*job;
	t_list		*process;

	if (pid <= 0)
		return (FAILURE);
	// global job
	job = g_job_head;
	while (job != NULL)
	{
		process = ((t_job*)job->data)->process_list;
		while (process != NULL)
		{
			if (((t_process*)process->data)->pid == pid)
				return (set_process_status(((t_process*)process->data)
							, pid, status));
			process = process->next;
		}
		job = job->next;
	}
	ft_dprintf(2, "[WARNING]: No child process %d.\n", (int)pid);
	return (FAILURE);
}

void		wait_for_job(t_job *job)
{
	int		status;
	pid_t	pid;

	pid = 0;
	pid = waitpid(WAIT_ANY, &status, WUNTRACED);
	while (update_process_status(pid, status) == SUCCESS
			&& job_is_stopped(job) == FALSE
			&& job_is_completed(job) == FALSE)
	{
		pid = waitpid(WAIT_ANY, &status, WUNTRACED);
	}
}
