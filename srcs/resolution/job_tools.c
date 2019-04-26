/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 14:18:25 by skuppers          #+#    #+#             */
/*   Updated: 2019/04/26 18:52:48 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"
#include "resolve.h"

t_list	*g_job_head;

uint8_t	job_is_stopped(t_job *job)
{
	t_list		*process;

	process = job->process_list;
	while (process)
	{
		if (!((t_process*)process)->completed
				&& !((t_process*)process)->stopped)
			return (0);
		process = process->next;
	}
	return (1);
}

uint8_t	job_is_completed(t_job *job)
{
	t_list		*process;

	process = job->process_list;
	while (process)
	{
		if (!((t_process*)process)->completed)
			return (0);
		process = process->next;
	}
	return (1);
}
