/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 11:04:41 by skuppers          #+#    #+#             */
/*   Updated: 2019/04/19 11:33:43 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "jobs.h"

job_t	*find_job(pid_t pgid)
{
	job_t *job;

	job = g_job_head;
	while (job)
	{
		if (job->pgid == pgid)
			return (job);
		job = job->next;
	}
	return (NULL);
}

uint8_t	job_is_stopped(job_t *job)
{
	process_t	*process;

	process = job->first_process;
	while (process)
	{
		if (!process->completed && !process->stopped)
			return (0);
		process = process->next;
	}
	return (1);
}

uint8_t	job_is_completed(job_t *job)
{
	process_t *process;

	process = job->first_process;
	while (process)
	{
		if (!process->completed)
			return (0);
		process = process->next;
	}
	return (1);
}
