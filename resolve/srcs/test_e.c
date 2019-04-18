/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_e.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 17:14:00 by nrechati          #+#    #+#             */
/*   Updated: 2019/04/18 17:41:21 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "resolve.h"

static int teste_cat(t_instr *cmd, char **env)
{
	cmd->ac = 2;
	cmd->av = ft_strsplit("cat -e", " ");
	cmd->env = env;
	cmd->fd_in = open("./file1", O_RDWR);
	cmd->fd_out = 1;
	cmd->fd_err = 2;
	cmd->gid = 0;
	if (!cmd->av)
		return (0);
	return (1);
}

t_list *test_e(void)
{
	t_list *test;

	test = NULL;
	add_to_test(&test, teste_cat);
	return (test);
}
