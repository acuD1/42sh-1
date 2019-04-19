/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 09:41:27 by skuppers          #+#    #+#             */
/*   Updated: 2019/04/19 14:13:07 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "jobs.h"

int8_t	update_process_status(pid_t pid, int status)
{
	job_t		*job;
	process_t	*process;

	if (pid > 0)
	{
		job = g_job_head;
		while (job)
		{
			process = job->first_process;
			while (process)
			{
				if (process->pid == pid)
				{
					process->status = status;
					if (WIFSTOPPED(status))
						process->stopped = 1;
					else
					{
						process->completed = 1;
						if (WIFSIGNALED(status))
							ft_dprintf(2, "%d: Terminated by signal: %d.\n", (int)pid, WTERMSIG(process->status));
					}
					return (0);
				}
				process = process->next;
			}
			job = job->next;
		}
		ft_dprintf(2, "No child process %d.\n", (int)pid);
		return (-1);
	}
	else if (pid == 0)
		return (-1);
	return (-1);
}

void	wait_for_job(job_t *job)
{
	int		status;
	pid_t	pid;

	pid = waitpid(WAIT_ANY, &status, WUNTRACED);
	while (!update_process_status(pid, status)
		&& !job_is_stopped(job)
		&& !job_is_completed(job))
			pid = waitpid(WAIT_ANY, &status, WUNTRACED);
}

void fork_child(job_t *job, process_t *process, char **env, int infile, int outfile)
{
	pid_t		pid;

	pid = fork();
	if (pid == 0)
	   launch_process(process, job->pgid, infile, outfile, job->fd->std_err, env);
	else if (pid < 0)
	{
		ft_dprintf(2, "Fork() failed.\n");
		exit(-2);
	}
	else
	{
					/* Parent process */
		process->pid = pid; 		// Set the childs pid
									// If shell is interactive
		if (!job->pgid) 			// If no pgid is set, set it.
			job->pgid = pid;
		setpgid(pid, job->pgid);	// Set the child's pgid
	}
}

void	launch_job(job_t *job, char **env)
{
	process_t	*proc;

	int			mypipe[2];
	int32_t		infile;
	int32_t		outfile;

	infile = job->fd->std_in;
	proc = job->first_process;

	while (proc)
	{
		if (proc->next)
		{
			if (pipe(mypipe) < 0)
				exit(-1);
			outfile = mypipe[1];
		}
		else
			outfile = job->fd->std_out;

		/* fork child */
		fork_child(proc, job, env, infile, outfile);


		if (infile != job->fd->std_in)
			close(infile);
		if (outfile != job->fd->std_out)
			close(outfile);
		infile = mypipe[0];
		proc = proc->next;
	}
	wait_for_job(job);
}

int main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;

	job_t *job_head;
	job_t *new1;
	job_t *new2;

	job_head = get_job3();
	new1 = get_job1();
	new2 = get_job2();
	g_job_head = job_head;

	job_head->next = new1;
	new1->next = new2;

	while (job_head)
	{
		launch_job(job_head, env);
		job_head = job_head->next;
	}

	return (0);
}
