/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_R.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 13:57:15 by nrechati          #+#    #+#             */
/*   Updated: 2019/04/26 14:03:37 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "resolve.h"
#include "reso.h"

static int		testr_ls(t_process *cmd, char **env)
{
	t_filedesc	fd;

	ft_bzero(&fd, sizeof(t_filedesc));
	fd.in = 0;
	fd.out = -1;
	close(4);
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

static int		testr_cat(t_process *cmd, char **env)
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

static int		testr_wc(t_process *cmd, char **env)
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

int				init_job_r(t_job *job)
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
	job->command = ft_strdup(EXEC_TEST_R);
	job->fd = fd;
	job->f_process = alst;
	if (job->command == NULL)
		return (0);
	return (1);
}

t_list			*test_r(void)
{
	t_list	*test;

	test = NULL;
	add_to_test(&test, testr_ls);
	add_to_test(&test, testr_cat);
	add_to_test(&test, testr_wc);
	return (test);
}
