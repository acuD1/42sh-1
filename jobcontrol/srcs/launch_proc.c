/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_proc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 10:40:50 by skuppers          #+#    #+#             */
/*   Updated: 2019/04/19 17:14:38 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "jobs.h"

static void		launch_process(process_t *process, int infile,
			   	int outfile, int errfile, char **env)
{
//	pid_t	pid;

	/*	Interactive shell implementation	*/

//	if (!pgid)
//		pgid = getpid();
//	ft_dprintf(2, "Child pid is %d.\n", getpid())

		/*  Set up signal handling  */
/*	Since it herited its behavior from the shell  */
	signal(SIGINT, SIG_DFL); // way more

	ft_dprintf(2, "Launching %s | in:%d out:%d err:%d.\n",
				process->av[0], infile, outfile, errfile);

	/*  Set up correct piping   */
	if (infile != STDIN_FILENO)
	{
		dup2(infile, STDIN_FILENO);
		close(infile);
	}
	if (outfile != STDOUT_FILENO)
	{
		dup2(outfile, STDOUT_FILENO);
		close(outfile);
	}
	if (errfile != STDERR_FILENO)
	{
		dup2(errfile, STDERR_FILENO);
		close(errfile);
	}

	/*	Exec the new process	*/
	ft_dprintf(2, "\n");
	execve(process->av[0], process->av, env);
	ft_dprintf(2, "[ERROR] - Execution failed: %s.\n", process->av[0]);
	exit(-1);
}

void fork_child(job_t *job, process_t *process, char **env, filedesc_t fd)
{
	pid_t		pid;

	pid = fork();
	if (pid == 0)
  launch_process(process, fd.std_in, fd.std_out, job->fd->std_err, env);
	else if (pid < 0)
	{
		ft_dprintf(2, "Fork() failed.\n");
		exit(-2);
	}
	else
	{
					/* This is job control  */
					/* Parent process 		*/
		process->pid = pid; 		// Set the childs pid
									// If shell is interactive
		if (!job->pgid) 			// If no pgid is set, set it.
			job->pgid = pid;
//		setpgid(pid, job->pgid);	// Set the child's pgid
	}
}

