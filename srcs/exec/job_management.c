/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_management.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 12:38:05 by cempassi          #+#    #+#             */
/*   Updated: 2019/05/07 14:24:18 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <signal.h>
# include <unistd.h>
# include "21sh.h"
# include "exec.h"

int				check_completed(t_list *lst)
{
	t_process	*process;

	if (lst == NULL)
		return (0);
	process = lst->data;
	if (process->completed == 0)
		return (1);
	else
		ft_lstiter(process->fd, close_fd);
	return(check_completed(lst->next));
}

void			delete_finished(t_process *process, int status)
{
	if (WIFEXITED(status))
	{
		process->completed = 1;
		process->status = WEXITSTATUS(status);
		ft_printf("EXITED ! Je suis ici | Status : %d\n", process->status);
		ft_lstdel(&process->fd, close_fd);
	}
	else if (WIFSIGNALED(status))
	{
		ft_printf("On est la! Status :%d\n", WTERMSIG(status));
		process->completed = 1;
		if (WTERMSIG(status) == SIGPIPE)
		{
			ft_dprintf(2, "Pipe broken, kill %s\n", process->av[0]);
			kill(process->pid, SIGQUIT);
		}
		else if (WTERMSIG(status) == SIGQUIT)
		{
			ft_dprintf(2, "21sh : %d quit  %s\n", process->pid, process->av[0]);
			kill(process->pid, SIGQUIT);
		}
		ft_lstdel(&process->fd, close_fd);
	}
}

void			wait_job(const int signo)
{
	t_job		*job;
	int			status;
	int			pid;
	t_list		*node;
	t_process	*process;

	job = g_shell->current_job->data;
	ft_printf("SIGCHLD (%d) Handeling\n", signo);
	if ((pid = waitpid(WAIT_ANY, &status, WUNTRACED)))
	{
		if ((node = ft_lstfind(job->process_list, &pid, find_process)))
		{
			process = node->data;
			delete_finished(process, status);
		}
	}
}
