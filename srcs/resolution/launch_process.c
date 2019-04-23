/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 13:13:52 by skuppers          #+#    #+#             */
/*   Updated: 2019/04/24 00:53:28 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"
#include "log.h"
#include "resolve.h"

static void		redirect_setup(t_process *process)
{
	if (process->fd.in != STDIN_FILENO)
		dup2(process->fd.in, STDIN_FILENO);
	if (process->fd.in != STDOUT_FILENO)
		dup2(process->fd.out, STDOUT_FILENO);
	if (process->fd.in != STDERR_FILENO)
		dup2(process->fd.err, STDERR_FILENO);
}

static void		execute_process(t_registry *shell, t_process *process)
{
	char		*path;

	signal(SIGINT, SIG_DFL); // way more
	ft_dprintf(2, "Launching %s | in:%d out:%d err:%d.\n",
				process->av[0]
				, process->fd.in
				, process->fd.out
				, process->fd.err);
	ft_dprintf(2, "%@s\n", "34","- - - - - [OUTPUT] - - - - - ");
	redirect_setup(process);
	path = ft_hmap_getdata(&shell->bin_hashmap, process->av[0]);
	if (execve(path, process->av, process->env) == -1)
	{
		ft_dprintf(2, "[ERROR] - Execution failed: %s.\n", process->av[0]);
		exit(-1);
	}
}

void launch_process(t_registry *shell, t_job *job, t_process *process)
{
	pid_t		pid;

	if ((pid = fork()))
	{
		process->pid = pid;
		if (!job->pgid)
			job->pgid = pid;
	}
	else if (pid < 0)
		exit(-2);
	else
	{
		if (job->pgid)
			setgid(job->pgid);
		execute_process(shell, process);
	}
}
