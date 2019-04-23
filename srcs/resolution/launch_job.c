/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_job.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 13:13:51 by skuppers          #+#    #+#             */
/*   Updated: 2019/04/24 00:35:10 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"
#include "log.h"
#include "resolve.h"

t_list *g_job_head;

void	launch_job(t_registry *shell, t_list *job_lst)
{
	t_job			*current_job;
	t_list			*process;

	g_job_head = job_lst;
	current_job = ((t_job*)job_lst->data);
	process = current_job->process_list;
	while (process)
	{
		launch_process(shell, current_job, ((t_process*)process->data));
		process = process->next;
	}
	wait_for_job(current_job);
	ft_lstdel(&current_job->process_list, delete_process);
}
