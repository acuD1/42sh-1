/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 13:13:52 by skuppers          #+#    #+#             */
/*   Updated: 2019/04/23 15:54:37 by skuppers         ###   ########.fr       */
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

static void		execute_process(t_process *process,
			   	t_filedesc *io, t_list *ev)
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
				process->av[0], io->in, io->out, io->err);

	/*  Set up correct piping   */
	if (io->in != STDIN_FILENO)
	{
		dup2(io->in, STDIN_FILENO);
		close(io->in);
	}
	if (io->out != STDOUT_FILENO && io->out != STDIN_FILENO)
	{
		dup2(io->out, STDOUT_FILENO);
		close(io->out);
	}
	if (io->err != STDERR_FILENO && io->err != STDIN_FILENO)
	{
		dup2(io->err, STDERR_FILENO);
		close(io->err);
	}
	char **environ = str_lst_to_tab(ev);
	/*	Exec the new process	*/
//	ft_dprintf(2, "\n");
	execve(process->av[0], process->av, environ);
	ft_dprintf(2, "[ERROR] - Execution failed: %s.\n", process->av[0]);
	exit(-1);
}

void launch_process(t_job *job, t_process *process, t_list *env, t_filedesc *io)
{
	pid_t		pid;

	pid = fork();
	if (pid == 0)
	  execute_process(process, io, env);
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
