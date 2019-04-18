/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_b.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 16:02:32 by nrechati          #+#    #+#             */
/*   Updated: 2019/04/18 16:43:27 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "resolve.h"

static int testb_ls(t_instr *cmd, char **env)
{
	cmd->ac = 2;
	cmd->av = ft_strsplit("ls -lhi", " ");
	cmd->env = env;
	cmd->fd_in = 0;
	cmd->fd_out = open("./tempfile", O_RDWR | O_APPEND | O_CREAT, 0666);
	cmd->fd_err = 2;
	cmd->gid = 0;
	if (!cmd->av)
		return (0);
	return (1);
}

t_list *test_b(void)
{
	t_list *test;

	test = NULL;
	add_to_test(&test, testb_ls);
	return (test);
}
