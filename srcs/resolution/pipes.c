/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 13:13:53 by skuppers          #+#    #+#             */
/*   Updated: 2019/04/23 21:46:17 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"
#include "log.h"
#include "resolve.h"

void	setup_pipes(t_job *job, t_list *process,
				t_filedesc *io_file, int my_pipe[2])
{
	ft_printf("data: %d.\n", ((t_process*)process->data)->fd.out);
	io_file->out = ((t_process*)process->data)->fd.out;
	io_file->err = ((t_process*)process->data)->fd.err;

	if (process->next && io_file->out == STDOUT_FILENO)
	{
		if (pipe(my_pipe))
			exit(-1);
		io_file->out = my_pipe[1];
	}
	else if (io_file->out != STDOUT_FILENO)
		io_file->out = ((t_process*)process->data)->fd.out;
	else
		io_file->out = job->fd.out;
}

void	cleanup_pipes(t_job *job, t_filedesc *io_file)
{
	if (io_file->in != job->fd.in)
		close(io_file->in);
	else if (io_file->out != job->fd.out)
		close(io_file->out);
}

void	link_pipes(t_list *process, t_filedesc *io_file, int my_pipe[2])
{
	if (process->next && io_file->out == my_pipe[1])
		io_file->in = my_pipe[0];
	else if (io_file->out != STDOUT_FILENO)
		close(io_file->out);
	else
		io_file->in = io_file->out;
}
