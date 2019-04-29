/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_O.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 14:43:34 by skuppers          #+#    #+#             */
/*   Updated: 2019/04/26 11:18:43 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "resolve.h"
#include "reso.h"

static int		testO_ls(t_process *cmd, char **env)
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

static int		testO_cat(t_process *cmd, char **env)
{
	t_filedesc	fd;

	ft_bzero(&fd, sizeof(t_filedesc));
	fd.in = 3;
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

static int		testO_wc(t_process *cmd, char **env)
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

int				init_job_o(t_job *job)
{
	int my_pipe[2];
	int my_pipe2[2];
	t_filedesc	fd;
	t_list		*alst;

	alst = NULL;
	pipe(my_pipe);
	pipe(my_pipe2);
	ft_bzero(&fd, sizeof(t_filedesc));
	fd.in = 0;
	fd.out = 1;
	fd.err = 2;
	job->command = ft_strdup(EXEC_TEST_O);
	job->fd = fd;
	job->f_process = alst;
	if (job->command == NULL)
		return (0);
	return (1);
}

t_list			*test_o(void)
{
	t_list	*test;

	test = NULL;
	add_to_test(&test, testO_ls);
	add_to_test(&test, testO_cat);
	add_to_test(&test, testO_wc);
	return (test);
}
