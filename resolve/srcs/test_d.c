/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 16:49:39 by nrechati          #+#    #+#             */
/*   Updated: 2019/04/18 17:01:18 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "resolve.h"

static int testd_ls(t_instr *cmd, char **env)
{
	cmd->ac = 2;
	cmd->av = ft_strsplit("ls -lhi 405", " ");
	cmd->env = env;
	cmd->fd_in = 0;
	cmd->fd_out = 1;
	cmd->fd_err = open("./errorfile", O_RDWR | O_APPEND | O_CREAT, 0666);
	cmd->gid = 0;
	if (!cmd->av)
		return (0);
	return (1);
}

t_list *test_d(void)
{
	t_list *test;

	test = NULL;
	add_to_test(&test, testd_ls);
	return (test);
}
