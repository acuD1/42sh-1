/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 09:41:27 by skuppers          #+#    #+#             */
/*   Updated: 2019/04/19 17:31:49 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "jobs.h"

int8_t set_process_status(process_t *process, pid_t pid,int status)
{
	process->status = status;
	if (WIFSTOPPED(status))
		process->stopped = 1;
	else
	{
		process->completed = 1;
		if (WIFSIGNALED(status))
		ft_dprintf(2, "%d: Terminated by %d.\n", pid, WTERMSIG(process->status));
	}
	return (0);

}

int8_t	update_process_status(pid_t pid, int status)
{
	job_t		*job;
	process_t	*process;

	if (pid <= 0)
		return (-1);
	job = g_job_head;
	while (job)
	{
		process = job->first_process;
		while (process)
		{
			if (process->pid == pid)
				return (set_process_status(process, pid, status));
			process = process->next;
		}
		job = job->next;
	}
	ft_dprintf(2, "No child process %d.\n", (int)pid);
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

uint8_t is_default_io(filedesc_t *fd)
{
	if (fd->std_in == STDIN_FILENO
     && fd->std_out == STDOUT_FILENO
	 && fd->std_err == STDERR_FILENO)
		return (1);
	return (0);
}

void	launch_job(job_t *job, char **env)
{
	filedesc_t	io_file;
	process_t	*proc;
	int			mypipe[2];

	io_file.std_in = job->fd->std_in;
	proc = job->first_process;
	ft_dprintf(1, "Launching: %s.\n", job->command);
	while (proc)
	{
		//set default std_fd's into io_file
//		io_file.std_in = proc->fd->std_in;   // 0
		io_file.std_out = proc->fd->std_out; // 1
		io_file.std_err = proc->fd->std_err; // 2

		if (io_file.std_out == STDOUT_FILENO) //is_default_io ?
		{
			if (proc->next) // if we have another process in the job (pipe)
			{
				if (pipe(mypipe) < 0)
					exit(-1);
				ft_dprintf(2, "Pipe created.\n");
				io_file.std_out = mypipe[1]; //output of current job is piped
			}
			else
				io_file.std_out = job->fd->std_out; // else set it to job_out
		}

		fork_child(job, proc, env, io_file);

		if (io_file.std_in != job->fd->std_in)
			close(io_file.std_in);
//		if (io_file.std_out != job->fd->std_out
//		 || )
			close(io_file.std_out);

//		if (proc->next)
		if (io_file.std_out == mypipe[1]  && proc->next)
			io_file.std_in = mypipe[0]; // input of next process is pipe[0];
		else
			io_file.std_in = io_file.std_out;
//		{
//			if (proc->next->fd->std_in == STDIN_FILENO)
//			else
//				io_file.std_in = proc->next->fd->std_in;
//		}

		proc = proc->next;
	}
	wait_for_job(job);
}

int main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;

	job_t *job_head;
//	job_t *new1;
//	job_t *new2;

	job_head = get_job1();
//	new1 = get_job1();
//	new2 = get_job2();
	g_job_head = job_head;

//	job_head->next = new1;
//	new1->next = new2;

	while (job_head)
	{
		launch_job(job_head, env);
		job_head = job_head->next;
	}

	return (0);
}
