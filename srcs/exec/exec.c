/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 02:19:00 by cempassi          #+#    #+#             */
/*   Updated: 2019/05/07 05:09:40 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "21sh.h"
#include "resolve.h"
#include "sig.h"

int				check_to_close(void *data, void *to_test)
{
	t_filedesc		*fd;
	void			*holder;

	holder = to_test;
	fd = data;
	if (fd->action & FD_CLOSE)
		return (0);
	return (1);
}

void			signal_execution(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGCHLD, SIG_DFL);
	signal(SIGSEGV, SIG_DFL);
	signal(SIGABRT, SIG_DFL);
	signal(SIGBUS, SIG_DFL);
}

int				find_process(void *data, void *to_find)
{
	t_process	*process;
	pid_t		*pid;

	process = data;
	pid = to_find;
	return (*pid == process->pid ? 1 : 0);
}

void			delete_finished(t_process *process, int status)
{
	if (WIFEXITED(status))
	{
		process->status = WEXITSTATUS(status);
		ft_lstdel(&process->fd, close_fd);
	}
	else if (WIFSIGNALED(status))
	{
		ft_dprintf(2, "Kill by %d\n", WTERMSIG(status));
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

void			signal_job(void)
{
	signal(SIGINT, kill_process);
	signal(SIGQUIT, kill_process);
	signal(SIGCHLD, wait_job);
}

int				execute_pid(t_process *process)
{
	t_builtin	builtin;
	char		*exec;

	ft_lstiter(process->fd, redirect);
	signal_execution();
	if ((builtin = ft_hmap_getdata(&g_shell->blt_hashmap, process->av[0])))
		builtin(g_shell, process->av);
	else if ((exec = ft_hmap_getdata(&g_shell->bin_hashmap, process->av[0])))
		execve(exec, process->av, process->env_tab);
	else if (process->av[0][0] == '.' || process->av[0][0] == '/')
		execve(process->av[0], process->av, process->env_tab);
	ft_dprintf(2, "21sh: command not found: %s\n", process->av[0]);
	exit(EXIT_FAILURE);
}

void		fork_process(void *data)
{
	t_process		*process;

	process = data;
	if (process->av == NULL)
		return;
	ft_printf("Je suis ici\n");
	process->env_tab = ft_lsttotab(process->env, variable_to_str);
	if ((process->pid = fork()) == SUCCESS)
		execute_pid(process);
	else if (process->pid < 0)
	{
		ft_dprintf(2, "[ERROR]: Fork() failed.\n");
		ft_freetab(&process->env_tab);
		process->status = -1;
	}
	else
	{
		ft_freetab(&process->env_tab);
		ft_lstremove_if(&process->fd, NULL, check_to_close, close_fd);
	}
}

int			run_builtin(t_process *process)
{
	t_builtin	builtin;

	if((builtin = ft_hmap_getdata(&g_shell->blt_hashmap, process->av[0])))
	{
		g_shell->cur_fd.in = 0;
		g_shell->cur_fd.out = 1;
		g_shell->cur_fd.err = 2;
		ft_lstiter(process->fd, get_blt_fd);
		builtin(g_shell, process->av);
		g_shell->cur_fd.in = 0;
		g_shell->cur_fd.out = 1;
		g_shell->cur_fd.err = 2;
		return (1);
	}
	return (0);
}

int			run_job(t_registry *shell)
{
	t_job	*job;

	signal_job();
	if (shell->current_job == NULL)
		return (FAILURE);
	job = shell->current_job->data;
	if (job->process_list->next == NULL && run_builtin(job->process_list->data))
		return(SUCCESS);
	else
		ft_lstiter(job->process_list, fork_process);
	return (0);
}
