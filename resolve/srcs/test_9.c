/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_9.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 11:10:01 by nrechati          #+#    #+#             */
/*   Updated: 2019/04/29 14:07:45 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "resolve.h"
#include "reso.h"

static int		test9_cat(t_process *cmd, char **env)
{
	t_filedesc	fd;

	ft_bzero(&fd, sizeof(t_filedesc));
	fd.in = 2;
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

int				init_job9(t_job *job)
{
	t_filedesc	fd;
	t_list		*alst;

	alst = NULL;
	ft_bzero(&fd, sizeof(t_filedesc));
	fd.in = 0;
	fd.out = 1;
	fd.err = 2;
	job->command = ft_strdup("cat");
	job->fd = fd;
	job->process_list = alst;
	if (job->command == NULL)
		return (0);
	return (1);
}


t_list			*test9(void)
{
	t_list	*test;

	test = NULL;
	add_to_test(&test, test9_cat);
	return (test);
}
