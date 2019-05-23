/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_P.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 14:46:02 by skuppers          #+#    #+#             */
/*   Updated: 2019/04/29 14:07:45 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "resolve.h"
#include "reso.h"

static int		testP_ls(t_process *cmd, char **env)
{
	t_filedesc	fd;

	ft_bzero(&fd, sizeof(t_filedesc));
	fd.in = 0;
	close(4);
	fd.out = open("testfile", O_RDWR | O_CREAT | O_TRUNC, 0644);
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

static int		testP_cat(t_process *cmd, char **env)
{
	t_filedesc	fd;

	ft_bzero(&fd, sizeof(t_filedesc));
	fd.in = 3;
	fd.out = 1;
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

int				init_job_p(t_job *job)
{
	int		my_pipe[2];
	t_filedesc	fd;
	t_list		*alst;

	alst = NULL;
	pipe(my_pipe);
	ft_bzero(&fd, sizeof(t_filedesc));
	fd.in = 0;
	fd.out = 1;
	fd.err = 2;
	job->command = ft_strdup(EXEC_TEST_P);
	job->fd = fd;
	job->process_list = alst;
	if (job->command == NULL)
		return (0);
	return (1);
}


t_list			*test_p(void)
{
	t_list	*test;

	test = NULL;
	add_to_test(&test, testP_ls);
	add_to_test(&test, testP_cat);
	return (test);
}