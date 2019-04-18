/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_7.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 15:43:22 by nrechati          #+#    #+#             */
/*   Updated: 2019/04/18 16:50:35 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "resolve.h"

static int		test7_ls(t_instr *cmd, char **env)
{
	cmd->ac = 2;
	cmd->av = ft_strsplit("ls -lai 404", " ");
	cmd->env = env;
	cmd->fd_in = 0;
	cmd->fd_out = 1;
	cmd->fd_err = open("./errorfile", O_RDWR | O_TRUNC | O_CREAT, 0666);
	cmd->gid = 0;
	if (!cmd->av)
		return (0);
	return (1);
}

t_list			*test7(void)
{
	t_list *test;

	test = NULL;
	add_to_test(&test, test7_ls);
	return (test);
}
