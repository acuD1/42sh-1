/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 10:51:12 by nrechati          #+#    #+#             */
/*   Updated: 2019/04/18 10:59:16 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "resolve.h"

static int		test2_cat(t_instr *cmd, char **env)
{
	cmd->ac = 2;
	cmd->av = ft_strsplit(EXEC_TEST_2, " ");
	cmd->env = env;
	cmd->fd_in = 0;
	cmd->fd_out = 1;
	cmd->fd_err = 2;
	cmd->gid = 0;
	if (!cmd->av)
		return (0);
	return (1);
}

t_list			*test2(void)
{
	t_list	*test;

	test = NULL;
	add_to_test(&test, test2_cat);
	return (test);
}
