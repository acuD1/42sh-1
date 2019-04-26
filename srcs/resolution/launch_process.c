/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 13:13:52 by skuppers          #+#    #+#             */
/*   Updated: 2019/04/26 10:53:38 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"
#include "log.h"
#include "resolve.h"

char		**str_lst_to_tab(t_list *alst)
{
	int		i;
	size_t	size;
	t_node	*data;
	char	*env;
	char	**tabs;

	i = 0;
	size = ft_lstlen(alst);
	if (!(tabs = (char **)malloc(sizeof(char *) * (size + 1))))
		return (NULL);
	while (alst != NULL)
	{
		data = (t_node *)alst->data;
		env = NULL;
		ft_asprintf(&env, "%s=%s", data->var, data->data);
		tabs[i] = env;
		alst = alst->next;
		i++;
	}
	tabs[i] = NULL;
	return (tabs);
}

static void		execute_process(t_process *process, t_registry *shell)
{
	t_filedesc		fd;

	fd = process->fd;
//	pid_t	pid;

	/*	Interactive shell implementation	*/

//	if (!pgid)
//		pgid = getpid();
//	ft_dprintf(2, "Child pid is %d.\n", getpid())

		/*  Set up signal handling  */
/*	Since it herited its behavior from the shell  */
	signal(SIGINT, SIG_DFL); // way more

	ft_dprintf(2, "\x1b[32m[CMD LAUNCH] %s | IN: %d OUT: %d ERR: %d\n\x1b[0m",
				process->av[0], fd.in, fd.out, fd.err);
	ft_dprintf(2, "\x1b[35m[OUTPUT]: _______________________\n\x1b[0m");

	/*  Set up correct piping   */
	if (fd.in != STDIN_FILENO && fd.in != STDOUT_FILENO && fd.in != STDERR_FILENO)
	{
		/* PROTECT DUP */
		if (fd.in != -1 || close(STDIN_FILENO))
		{
			dup2(fd.in, STDIN_FILENO);
			//close(fd.in);
		}
	}
	if (fd.out != STDOUT_FILENO && fd.out != STDIN_FILENO)
	{
		if (fd.out != -1 || close(STDOUT_FILENO))
		{
			dup2(fd.out, STDOUT_FILENO);
			//if (fd.out != STDERR_FILENO)
			//	close(fd.out);
		}
	}
	if (fd.err != STDERR_FILENO && fd.err != STDIN_FILENO)
	{
		if (fd.err != -1 || close(STDERR_FILENO))
		{
			if (fd.err == STDOUT_FILENO)
				dup2(fd.out, STDERR_FILENO);
			else
				dup2(fd.err, STDERR_FILENO);
			//if (fd.err != STDOUT_FILENO)
			//	close(fd.err);
		}
	}
	char **environ = str_lst_to_tab(shell->env);
	/*	Exec the new process	*/
	execve(ft_hmap_getdata(&shell->bin_hashmap, process->av[0]), process->av, environ);
	ft_dprintf(2, "[ERROR] - Execution failed: %s.\n", process->av[0]);
	exit(-1);
}

void launch_process(t_job *job, t_process *process, t_registry *shell)
{
	pid_t		pid;

	/*
	 *	if process is builtin and not in a pipe
	 *		launch it with no fork
	 *	else
	 *		fork() the process
	 */

//	if (ft_hmap_getdata(&shell->blt_hashmap, process->av[0]) != 0)


	pid = fork();
	if (pid == 0)
		execute_process(process, shell);
	else if (pid < 0)
	{
//		ft_dprintf(2, "Fork() failed.\n");
		exit(-2);
	}
	else
	{
		process->pid = pid; 		// Set the childs pid
									// If shell is interactive
		if (!job->pgid) 			// If no pgid is set, set it.
			job->pgid = pid;
//		setpgid(pid, job->pgid);	// Set the child's pgid
	}
}
