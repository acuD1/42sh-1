/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_job.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 13:13:51 by skuppers          #+#    #+#             */
/*   Updated: 2019/04/24 18:48:47 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"
#include "log.h"
#include "resolve.h"

t_list *g_job_head;

static void	close_opened_fd(t_filedesc fd)
{
	if (fd.in != STDIN_FILENO && fd.in != -1)
		close(fd.in);
	if (fd.out != STDOUT_FILENO && fd.out != -1)
		close(fd.out);
	if (fd.err != STDERR_FILENO && fd.err != STDOUT_FILENO && fd.err != -1)
		close(fd.err);
}

void		launch_job(t_registry *shell, t_list *job_lst)
{
	t_job			*current_job;
	t_list			*process;

	g_job_head = job_lst;
	current_job = ((t_job*)job_lst->data);
	process = current_job->f_process;

	ft_dprintf(2, "\x1b[32m[JOB LAUNCH]: %s || IN = %d\n\x1b[0m"
				, current_job->command, ((t_process*)current_job->f_process->data)->fd.in);
	while (process)
	{
		launch_process(current_job, ((t_process*)process->data), shell);
		close_opened_fd(((t_process *)process->data)->fd);
		process = process->next;
	}
	wait_for_job(current_job);
}
