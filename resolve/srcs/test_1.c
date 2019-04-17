/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 09:41:02 by nrechati          #+#    #+#             */
/*   Updated: 2019/04/17 17:17:20 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "resolve.h"

int		test1_ls(t_instr *cmd, char **env)
{
	cmd->ac = 4;
	cmd->av = ft_strsplit(EXEC_TEST_1, " ");
	cmd->env = env;
	cmd->fd_in = 0;
	cmd->fd_out = 1;
	cmd->fd_err = 2;
	cmd->gid = 0;
	if (!cmd->av)
		return (0);
	return (1);
}

t_list	*test1(void)
{
	t_list	*test;

	test = NULL;
	add_to_test(&test, test1_ls);
	return (test);
}
