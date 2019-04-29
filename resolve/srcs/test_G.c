/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_G.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 14:24:05 by nrechati          #+#    #+#             */
/*   Updated: 2019/04/24 14:30:05 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "resolve.h"
#include "reso.h"

static int		test_g_ls(t_process *cmd, char **env)
{
	t_filedesc	fd;

	ft_bzero(&fd, sizeof(t_filedesc));
	fd.in = 0;
	fd.out = 1;
	fd.err = -1;
	cmd->av = ft_strsplit("ls 404", " ");
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

int				init_job_g(t_job *job)
{
	t_filedesc	fd;
	t_list		*alst;

	alst = NULL;
	ft_bzero(&fd, sizeof(t_filedesc));
	fd.in = 0;
	fd.out = 1;
	fd.err = 2;
	job->command = ft_strdup("ls");
	job->fd = fd;
	job->f_process = alst;
	if (job->command == NULL)
		return (0);
	return (1);
}

t_list			*test_g(void)
{
	t_list	*test;

	test = NULL;
	add_to_test(&test, test_g_ls);
	return (test);
}
