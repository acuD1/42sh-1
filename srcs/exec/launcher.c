/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launcher.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 12:38:04 by cempassi          #+#    #+#             */
/*   Updated: 2019/05/07 14:24:45 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "21sh.h"
#include "exec.h"
#include "parser.h"
#include "resolve.h"
#include "sig.h"
#include "interface_functions.h"

int			execute_pid(t_process *process)
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
