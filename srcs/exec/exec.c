/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 02:19:00 by cempassi          #+#    #+#             */
/*   Updated: 2019/05/13 11:56:47 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "21sh.h"
#include "resolve.h"
#include "interface_functions.h"

void			process_status(void *data)
{
	t_process *process;

	process = data;
	ft_printf("Process : %s | Status : %d | PID : %d\n", process->av[0],
			process->completed, process->pid);
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

int				find_process(void *data, void *to_find)
{
	t_process	*process;
	pid_t		*pid;

	process = data;
	pid = to_find;
	return (*pid == process->pid ? 1 : 0);
}