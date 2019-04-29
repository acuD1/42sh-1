/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_Q.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 12:57:49 by nrechati          #+#    #+#             */
/*   Updated: 2019/04/29 14:07:45 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "resolve.h"
#include "reso.h"

static int		testq_ls(t_process *cmd, char **env)
{
	t_filedesc	fd;

	ft_bzero(&fd, sizeof(t_filedesc));
	fd.in = 0;
	fd.out = 4;
	fd.err = 2;
	cmd->av = ft_strsplit("ls -l", " ");
	cmd->env = env;
	cmd->pid = 0;
	cmd->completed = 0;
	cmd->stopped = 0;
	cmd->status = 0;
	cmd->fd = fd;
	if (!cmd->av)
		return (0);
	return (1);
}

static int		testq_cat(t_process *cmd, char **env)
{
	t_filedesc	fd;

	ft_bzero(&fd, sizeof(t_filedesc));
	fd.in = 2;
	fd.out = 6;
	fd.err = 2;
	cmd->av = ft_strsplit("cat -e", " ");
	cmd->env = env;
	cmd->pid = 0;
	cmd->completed = 0;
	cmd->stopped = 0;
	cmd->status = 0;
	cmd->fd = fd;
	if (!cmd->av)
		return (0);
	return (1);
}

static int		testq_wc(t_process *cmd, char **env)
{
	t_filedesc	fd;

	ft_bzero(&fd, sizeof(t_filedesc));
	fd.in = 5;
	fd.out = 1;
	fd.err = 2;
	cmd->av = ft_strsplit("wc -l", " ");
	cmd->env = env;
	cmd->pid = 0;
	cmd->completed = 0;
	cmd->stopped = 0;
	cmd->status = 0;
	cmd->fd = fd;
	if (!cmd->av)
		return (0);
	return (1);
}

int				init_job_q(t_job *job)
{
	int my_pipe[2];
	int my_pipe2[2];
	t_filedesc	fd;
	t_list		*alst;

	alst = NULL;
	pipe(my_pipe);
	pipe(my_pipe2);
	ft_printf("Pipe 1 : INT = %d || OUT = %d\n", my_pipe[0], my_pipe[1]);
	ft_printf("Pipe 2 : INT = %d || OUT = %d\n", my_pipe2[0], my_pipe2[1]);
	ft_bzero(&fd, sizeof(t_filedesc));
	fd.in = 0;
	fd.out = 1;
	fd.err = 2;
	job->command = ft_strdup(EXEC_TEST_Q);
	job->fd = fd;
	job->process_list = alst;
	if (job->command == NULL)
		return (0);
	return (1);
}

t_list			*test_q(void)
{
	t_list	*test;

	test = NULL;
	add_to_test(&test, testq_ls);
	add_to_test(&test, testq_cat);
	add_to_test(&test, testq_wc);
	return (test);
}
