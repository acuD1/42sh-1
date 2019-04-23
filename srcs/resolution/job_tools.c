/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 14:18:25 by skuppers          #+#    #+#             */
/*   Updated: 2019/04/23 15:29:30 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"
#include "log.h"
#include "resolve.h"

t_list	*g_job_head;

t_job	*find_job(pid_t pgid)
{
	t_list *job;

	job = g_job_head;
	while (job)
	{
		if (((t_job*)job)->pgid == pgid)
			return ((t_job*)job);
		job = job->next;
	}
	return (NULL);
}

uint8_t	job_is_stopped(t_job *job)
{
	t_list		*process;

	process = job->f_process;
	while (process)
	{
		if (!((t_process*)process)->completed && !((t_process*)process)->stopped)
			return (0);
		process = process->next;
	}
	return (1);
}

uint8_t	job_is_completed(t_job *job)
{
	t_list		*process;

	process = job->f_process;
	while (process)
	{
		if (!((t_process*)process)->completed)
			return (0);
		process = process->next;
	}
	return (1);
}
