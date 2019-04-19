/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_proc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 10:40:50 by skuppers          #+#    #+#             */
/*   Updated: 2019/04/19 14:13:08 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "jobs.h"

void	launch_process(process_t *process, pid_t pgid,
				int infile, int outfile, int errfile,
				char **env)
{
//	pid_t	pid;
//	pid = pgid;
	(void)pgid;

	/*	Interactive shell implementation	*/

	/*  Set up signal handling  */
	/*	Since it herited its behavior from the shell  */
	signal(SIGINT, SIG_DFL); // way more

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
	execve(process->av[0], process->av, env);
	ft_dprintf(2, "[ERROR] - Execution failed: %s.\n", process->av[0]);
	exit(-1);
}
