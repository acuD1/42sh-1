/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_job.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 13:13:51 by skuppers          #+#    #+#             */
/*   Updated: 2019/04/23 18:16:34 by nrechati         ###   ########.fr       */
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
	t_filedesc		io_file;
	int				my_pipe[2];

	g_job_head = job_lst;
	current_job = ((t_job*)job_lst->data);
	process = current_job->f_process;
	io_file.in = current_job->fd.in;

	ft_printf("|--> Launching job: %s.\n", current_job->command);
	while (process)
	{
		setup_pipes(current_job, process, &io_file, my_pipe);
//		ft_printf("execve\n");
		launch_process(current_job, ((t_process*)process->data), shell, &io_file);

		if (process->next != NULL)
		{
			cleanup_pipes(current_job, &io_file);
			link_pipes(process, &io_file, my_pipe);
		}
		process = process->next;
	}
	wait_for_job(current_job);
}
