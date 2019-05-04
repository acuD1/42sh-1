/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_job.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 13:13:51 by skuppers          #+#    #+#             */
/*   Updated: 2019/05/04 15:30:21 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "resolve.h"
#include "sig.h"
#include "interface_functions.h"
#include <unistd.h>

t_list *g_job_head;

void			close_fd(t_list *data)
{
	t_filedesc		*fd;

	fd = data->data;
	if (fd->first > 2)
		close(fd->first);
	if (fd->second > 2)
		close(fd->second);
}

static void		get_last_bin(t_registry *shell, t_process *process, char **cmd)
{
	if (ft_hmap_getdata(&shell->bin_hashmap, process->av[0]) != NULL)
		ft_asprintf(cmd, "%s"
				, ft_hmap_getdata(&shell->bin_hashmap, process->av[0]));
	else if (process->av[0][0] == '.' || process->av[0][0] == '/')
	{
		if (access(process->av[0], F_OK) == SUCCESS
				|| access(process->av[0], X_OK) == SUCCESS)
			ft_asprintf(cmd, "%s", process->av[0]);
	}
}

static int		change_last_bin(t_process *process, t_registry *shell)
{
	char	*asp;

	asp = NULL;
	if (get_env_var(shell, "_") != NULL)
	{
		if (ft_hmap_getdata(&shell->blt_hashmap, process->av[0]) == NULL)
		{
			get_last_bin(shell, process, &asp);
			if (asp == NULL || change_node(&shell->env, "_", asp) == FAILURE)
				return (FAILURE);
		}
	}
	else
	{
		if (ft_hmap_getdata(&shell->blt_hashmap, process->av[0]) == NULL)
		{
			get_last_bin(shell, process, &asp);
			if (asp == NULL || s_create_node(&shell->env, "_", asp) == FAILURE)
				return (FAILURE);
		}
		free(asp);
	}
	return (SUCCESS);
}

static int		update_last_bin(t_list *process_lst, t_registry *shell)
{
	t_list	*ptr;

	ptr = process_lst;
	while (ptr->next)
	{
		change_last_bin(ptr->data, shell);
		ptr = ptr->next;
	}
	change_last_bin(ptr->data, shell);
	return (0);
}

void			launch_job(t_registry *shell, t_list *job_lst)
{
	t_job			*current_job;
	t_list			*process_lst;

	if (shell->is_interactive == TRUE)
	{
		restore_term_behavior(shell);
		define_execution_signals();
	}
	g_job_head = job_lst;
	current_job = ((t_job *)job_lst->data);
	process_lst = current_job->process_list;
	while (process_lst != NULL)
	{
		launch_process(current_job, ((t_process*)process_lst->data), shell);
		if (((t_process *)process_lst->data)->fd)
			ft_lstiter(((t_process *)process_lst->data)->fd, close_fd);
		process_lst = process_lst->next;
	}
	wait_for_job(current_job);
	update_last_bin(current_job->process_list, shell);
	if (shell->is_interactive == TRUE)
	{
		set_term_behavior(shell);
		define_ign_signals();
	}
}
