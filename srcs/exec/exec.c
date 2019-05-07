/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 02:19:00 by cempassi          #+#    #+#             */
/*   Updated: 2019/05/07 12:12:24 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>
#include "21sh.h"
#include "resolve.h"
#include "interface_functions.h"
#include "sig.h"

void			process_status(void *data)
{
	t_process *process;

	process = data;
	ft_printf("Process : %s | Status : %d | PID : %d\n", process->av[0],
			process->completed, process->pid);
}

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

int				check_to_close(void *data, void *to_test)
{
	t_filedesc		*fd;
	void			*holder;

	holder = to_test;
	fd = data;
	if (fd->action & FD_CLOSE)
	{
		ft_printf("Closing fd %d\n", fd->second);
		return (0);
	}
	return (1);
}

void			signal_ignore(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGCHLD, SIG_IGN);
	signal(SIGSEGV, SIG_IGN);
	signal(SIGABRT, SIG_IGN);
	signal(SIGBUS, SIG_IGN);
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

//void			signal_handler(t_process *process, int status)
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

void			kill_one_process(int signo)
{
	int		pid;
	int		status;

	ft_printf("Je suis ici! Signo : %s\n", signo);
	pid = wait(&status);
	kill(pid, SIGQUIT);
}

void			signal_job(void)
{
	signal(SIGQUIT, exit_program);
	signal(SIGINT, kill_process);
	signal(SIGCHLD, wait_job);
	signal(SIGPIPE, kill_process);
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
		restore_term_behavior(g_shell);
	}
}

int			run_builtin(t_process *process)
{
	t_builtin	builtin;

	if (process->av == NULL)
		return (1);
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
	int		job_status;

	job_status = 1;
	if (shell->current_job == NULL)
		return (FAILURE);
	set_term_behavior(shell);
	signal_job();
	job = shell->current_job->data;
	if (job->process_list->next == NULL && run_builtin(job->process_list->data))
		ft_lstdel(&job->process_list, close_fd);
	else if (((t_process *)job->process_list->data)->av != NULL)
		ft_lstiter(job->process_list, fork_process);
	else
		ft_lstdel(&job->process_list, close_fd);
	while (check_completed(job->process_list))
		;
	signal_ignore();
	define_interface_signals();
	return (0);
}
