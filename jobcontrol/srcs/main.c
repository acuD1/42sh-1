/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 09:41:27 by skuppers          #+#    #+#             */
/*   Updated: 2019/04/23 10:45:23 by skuppers         ###   ########.fr       */
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

void	setup_piping(filedesc_t *io_file, int mypipe[2], job_t *job, process_t *proc)
{
		io_file->std_out = proc->fd->std_out; // 1 or file
//		io_file->std_err = proc->fd->std_err; // 2 or file

		if (proc->next && io_file->std_out == STDOUT_FILENO)
		{
			if (pipe(mypipe) < 0)
				exit(-1);
			io_file->std_out = mypipe[1]; //output of current job is piped
		}
		else if (io_file->std_out != STDOUT_FILENO)
			io_file->std_out = proc->fd->std_out;
		else
			io_file->std_out = job->fd->std_out; // else set it to job_out

}

void	cleanup_pipes(filedesc_t *io_file, job_t *job)
{
	if (io_file->std_in != job->fd->std_in)
		close(io_file->std_in);
	if (io_file->std_out != job->fd->std_out)
		close(io_file->std_out);
}

void	close_pipes(filedesc_t *io_file, int mypipe[2], process_t *proc)
{
	if (proc->next && io_file->std_out == mypipe[1])
		io_file->std_in = mypipe[0]; // input of next process is pipe[0];
	else if (io_file->std_out != STDOUT_FILENO)
		close(io_file->std_in);
	else
		io_file->std_in = io_file->std_out;
}

void	launch_job(job_t *job, char **env)
{
	filedesc_t	io_file;
	process_t	*proc;
	int			mypipe[2];

	io_file.std_in = job->fd->std_in;
	proc = job->first_process;
	ft_dprintf(1, "Launching: (%s).\n", job->command);
	while (proc)
	{
		setup_piping(&io_file, mypipe, job, proc);

//------------------------------------------------|
		fork_child(job, proc, env, io_file);//    |
//------------------------------------------------|

		cleanup_pipes(&io_file, job);

		close_pipes(&io_file, mypipe, proc);

		proc = proc->next;
	}
	wait_for_job(job);
}

int main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;

	job_t *job;

	if (ac < 2)
	{
		ft_printf("Please enter a job to test. (1, 2, 3)\n");
		exit(-1);
	}
	if (av[1][0] == 49)
		job = get_job1();
	if (av[1][0] == 50)
		job = get_job2();
	if (av[1][0] == 51)
		job = get_job3();
	if (av[1][0] == 52)
		job = get_job4();
	if (av[1][0] == 53)
		job = get_job5();
	g_job_head = job;

	while (job)
	{
		launch_job(job, env);
		job = job->next;
	}
	return (0);
}
