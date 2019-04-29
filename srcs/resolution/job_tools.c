/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 14:18:25 by skuppers          #+#    #+#             */
/*   Updated: 2019/04/29 16:15:52 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"
#include "resolve.h"

t_list	*g_job_head;

uint8_t	job_is_stopped(t_job *job)
{
	t_list		*process;

	process = job->process_list;
	while (process != NULL)
	{
		if (((t_process *)process->data)->completed == FALSE
				&& ((t_process *)process->data)->stopped == FALSE)
			return (FALSE);
		process = process->next;
	}
	return (TRUE);
}

uint8_t	job_is_completed(t_job *job)
{
	t_list		*process;

	process = job->process_list;
	while (process != NULL)
	{
		if (((t_process*)process->data)->completed == FALSE)
			return (FALSE);
		process = process->next;
	}
	return (TRUE);
}
